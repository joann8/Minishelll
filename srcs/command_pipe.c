/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:42:47 by jacher            #+#    #+#             */
/*   Updated: 2021/04/21 19:14:32 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int			execute_pipe(t_simple_cmd *tmp_c, t_list **env, t_pipe *p,
				t_list **error)
{
	int res;

	p->fd_in_to_use = tmp_c->fd_in;//deja avec les redir
	p->fd_out_to_use = tmp_c->fd_out;//deja avec les redir
	p->fd_err_to_use = STDERR_FILENO;
	if (tmp_c->pipe_mod == 1)// si je suis piped
	{
		if (prepare_pipe_execution(tmp_c, p) == -1)//erreur fonction pipe
		{
			add_err_lst(error, strerror(errno), NULL, NULL);
			return (-1);//erreur pipe (fd_tab)
		}
	}
	//printf("tmp_c->on == %d\n", tmp_c->on);
	if (tmp_c->on == 1)
	{
	//	printf("here\n");
		res = execute_cmd(tmp_c, env, error, p);//COMMAND EXECUTION
		if (res == -1) //erreur malloc
			ft_putstr_fd("Error command execution\n", 2);//pas sure
		update_fd_pipes(tmp_c, p);
		return (res);
	}
	update_fd_pipes(tmp_c, p);
	return (0);
}

int			prepare_pipe(t_list **cmd_list, t_simple_cmd *tmp_c, t_seq *tmp_s,
				t_list **error)
{
	t_list	*new;
	t_list	*tmp_l;

	new = ft_lstnew((void*)tmp_c);
	if (new == NULL)
	{
		free(tmp_c);
		return (p_error(0, "malloc error\n", -1));
	}
	ft_lstadd_back(cmd_list, new);//tmp_c géré avec la liste maintenant
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

int			prepare_and_execute_pipe(t_list **cmd_list, t_list **env,
				t_seq *tmp_s)
{
	t_pipe			p;
	t_simple_cmd	*tmp_c;
	t_list			*error;
	int				res;

	error = NULL;
	//prepare pipe?
	p.fd_in_next = -1;
	while (tmp_s)
	{
		if ((tmp_c = malloc(sizeof(t_simple_cmd))) == NULL)
			return (p_error(0, "malloc error\n", -1));
		if (prepare_pipe(cmd_list, tmp_c, tmp_s, &error) == -1)
		{
			ft_lstclear(&error, free);
			return (-1);
		}
		res = execute_pipe(tmp_c, env, &p, &error);//0 OK, 19 exit, -1 malloc
		if (res != 0)		
		{
			//on veut aller au next input;
			if (res != 19)//si exit
				print_cmd_error(0, error);
			ft_lstclear(&error, free);
			return (res);
		}
		tmp_s = tmp_s->next_pipe;
	}
	print_cmd_error(0, error);
	ft_lstclear(&error, free);
	//clean pipes?
	return (0);//pour continuer
}

int		create_command(t_list *cmd_list, t_seq *tab_seq, int seq_nb,
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
		res = prepare_and_execute_pipe(&cmd_list, env, tmp_s);
		if (res != 0)//-1 pbm fonction pipe , 1 pbl exec
			return (res);
		i++;
	}
	return (0);
}
