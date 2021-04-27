/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:42:47 by jacher            #+#    #+#             */
/*   Updated: 2021/04/27 19:35:11 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int			prepare_cmd(t_simple_cmd *tmp_c, t_seq *tmp_s, t_list **env)
{
	t_list	*tmp_l;

	tmp_c->ac = ft_lstsize(tmp_s->word);
	tmp_c->av = malloc(sizeof(char*) * (tmp_c->ac + 1));
	tmp_c->on = 1;
	if (tmp_c->av == NULL)
		return (p_error(0, "malloc error\n", -1));
	if (assign_list_word(tmp_s, tmp_c) == -1)//erreur de malloc slmt
		return (-1); //gérée dans list assign word
	assign_pipes(tmp_s, tmp_c);
	tmp_l = tmp_s->redir;
	if (assign_list_redir(tmp_l, tmp_c, env) == -1)
		return (-1);
	tmp_c->p.fd_in_to_use = tmp_c->fd_in;
	tmp_c->p.fd_out_to_use = tmp_c->fd_out;
	tmp_c->next_pipe = NULL;
	return (0);
}

int			prepare_and_execute_non_piped_cmd(t_list **env, t_seq *tmp_s)
{
	t_simple_cmd	*tmp_c;
	int				res;

	res = 0;
	if ((tmp_c = malloc(sizeof(t_simple_cmd))) == NULL)
		return (p_error(0, "malloc error\n", -1));
	if (prepare_cmd(tmp_c, tmp_s, env) == -1)
		return (-1);
	if (tmp_c->on == 1)
		res = execute_non_piped(tmp_c, env);//0 OK, 227 exit, -1 malloc
	else
		g.exit_status = 1;
	free(tmp_c);
	return (res);
}

int			prepare_and_execute_piped_cmd(t_list **env, t_seq *tmp_s)
{
	t_simple_cmd	*tmp_c;
	int				res;
	t_simple_cmd	*begin;

	if ((tmp_c = malloc(sizeof(t_simple_cmd))) == NULL)
		return (p_error(0, "malloc error\n", -1));
	begin = tmp_c;
	begin->p.size = 0;
	while (tmp_s)
	{
		if (prepare_cmd(tmp_c, tmp_s, env) == -1)
			return (-1);
		begin->p.size += 1;
		if (tmp_s->next_pipe)
		{
			if ((tmp_c->next_pipe = malloc(sizeof(t_simple_cmd))) == NULL)
				return (p_error(0, "malloc error\n", -1));
			tmp_c = tmp_c->next_pipe;
		}
		tmp_s = tmp_s->next_pipe;
	}
	res = execute_piped(begin, env);//0 OK, 227 exit, -1 malloc
	ft_free_command_list(begin);
	return (res);
}

int			create_command(t_seq *tab_seq, int seq_nb, t_list **env)
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
		if (tmp_s->next_pipe == NULL)
			res = prepare_and_execute_non_piped_cmd(env, tmp_s);
		else
			res = prepare_and_execute_piped_cmd(env, tmp_s);
		if (res != 0)//-1 pbm fonction pipe , 1 pbl exec
			return (res);
		i++;
	}
	return (0);
}
