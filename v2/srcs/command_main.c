/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:42:47 by jacher            #+#    #+#             */
/*   Updated: 2021/04/23 20:52:23 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int			prepare_cmd(t_simple_cmd *tmp_c, t_seq *tmp_s, t_list **error)
{
//	t_list	*new;
	t_list	*tmp_l;

/*	new = ft_lstnew((void *)tmp_c);
	if (new == NULL)
	{
		free(tmp_c);
		return (p_error(0, "malloc error\n", -1));
	}
	ft_lstadd_back(cmd_list, new);//tmp_c géré avec la liste maintenant*/
	tmp_c->on = 1;
	tmp_c->ac = ft_lstsize(tmp_s->word);
	tmp_c->av = malloc(sizeof(char*) * (tmp_c->ac + 1));
	if (tmp_c->av == NULL)
		return (p_error(0, "malloc error\n", -1));
	if (assign_list_word(tmp_s, tmp_c) == -1)//erreur de malloc slmt
		return (-1); //gérée dans list assign word
	assign_pipes(tmp_s, tmp_c);
	tmp_l = tmp_s->redir;
	if (assign_list_redir(tmp_l, tmp_c, error) == -1)
		return (-1);
	return (0);
}

int			execute_non_piped(t_simple_cmd *tmp_c, t_list **env, t_list **error)
{
	int res;

	res = 0;
	tmp_c->p.fd_in_to_use = tmp_c->fd_in;//deja avec les redir
	tmp_c->p.fd_out_to_use = tmp_c->fd_out;//deja avec les redir
	res = execute_cmd_non_piped(tmp_c, env, error);//COMMAND EXECUTION//0 OK, 227 exit, -1 malloc
	if (res != 0)//erreur malloc ou exit
	{
		if (res == 227)
			print_cmd_error(0, *error);
		ft_lstclear(error, free);
		if (res == -1)
			ft_putstr_fd("Error command execution\n", 2);//pas sure
	}
	return (res);
}

int			prepare_and_execute_cmd(t_list **cmd_list, t_list **env,
				t_seq *tmp_s)
{
//	t_pipe			p;
	t_simple_cmd	*tmp_c;
	t_list			*error;
	int				res;

	(void)cmd_list;
	error = NULL;
	//p.fd_in_next = -1;
	if (tmp_s->next_pipe == NULL)
	{
		if ((tmp_c = malloc(sizeof(t_simple_cmd))) == NULL)
			return (p_error(0, "malloc error\n", -1));
		if (prepare_cmd(tmp_c, tmp_s, &error) == -1)
			return (-1);
		res = execute_non_piped(tmp_c, env, &error);//0 OK, 227 exit, -1 malloc
		free(tmp_c);
		return (res);
	}
	else
	{
		t_simple_cmd	*begin;
		int				count;
		count = 0;
		
		if ((tmp_c = malloc(sizeof(t_simple_cmd))) == NULL)
			return (p_error(0, "malloc error\n", -1));
		begin = tmp_c;
		while (tmp_s)
		{
			if (prepare_cmd(tmp_c, tmp_s, &error) == -1)
				return (-1);
			tmp_c->p.fd_in_to_use = tmp_c->fd_in;//deja avec les redir
			tmp_c->p.fd_out_to_use = tmp_c->fd_out;//deja avec les redir
			count++;
			if (tmp_s->next_pipe)
			{
				if ((tmp_c->next_pipe = malloc(sizeof(t_simple_cmd))) == NULL)
					return (p_error(0, "malloc error\n", -1));
				tmp_c = tmp_c->next_pipe;
			}
			tmp_s = tmp_s->next_pipe;
		}
		print_cmd_piped(begin);
		res = execute_piped(begin, env, &error, count);//0 OK, 227 exit, -1 malloc
		/*	if (res != 0)
			return (res);*/
		free(begin);
		return(0);
	}
	print_cmd_error(0, error);
	ft_lstclear(&error, free);
	return (0);//pour continuer
}

int			create_command(t_list *cmd_list, t_seq *tab_seq, int seq_nb,
				t_list **env)
{
	int				i;
	t_seq			*tmp_s;
	int				res;

	i = 0;
	while (i < seq_nb)
	{
		tmp_s = &tab_seq[i];
		if (make_expansion(tmp_s, env) == -1)
			return (-1);//erreur malloc
		res = prepare_and_execute_cmd(&cmd_list, env, tmp_s);
		if (res != 0)//-1 pbm fonction pipe , 1 pbl exec
			return (res);
		i++;
	}
	return (0);
}
