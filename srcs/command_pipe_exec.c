/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pipe_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:42:47 by jacher            #+#    #+#             */
/*   Updated: 2021/04/21 18:53:14 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	update_fd_pipes(t_simple_cmd *tmp_c, t_pipe *p)
{
	if (tmp_c->pipe_mod == 1)
	{
		if (tmp_c->pipe_pos == -1)//first
			close(p->fd_tab[1]);
		else if (tmp_c->pipe_pos == 1)//dernier
			close(p->fd_in_next);
		else if (tmp_c->pipe_pos == 0)
		{
			close(p->fd_in_next);
			close(p->fd_tab[1]);
		}
		close(p->fd_tab_err[0]);
		close(p->fd_tab_err[1]);
		p->fd_in_next = p->fd_tab[0];
	}
	if (tmp_c->fd_in != STDIN_FILENO)
		close(tmp_c->fd_in);
	if (tmp_c->fd_out != STDOUT_FILENO)
		close(tmp_c->fd_out);
}

int		prepare_pipe_execution(t_simple_cmd *tmp_c, t_pipe *p)
{
	if (tmp_c->pipe_pos != 1)//si je suis piped mais pas le dernier
	{
		if (pipe(p->fd_tab) == -1)
			return (-1);
		if (pipe(p->fd_tab_err) == -1)//
			return (-1);//
	}
	if (tmp_c->pipe_pos == -1)//first//fd in reste le meme
	{
		if (p->fd_out_to_use == STDOUT_FILENO)
			p->fd_out_to_use = p->fd_tab[1];
		p->fd_err_to_use = p->fd_tab_err[1];//
	}
	else if (tmp_c->pipe_pos == 1)//dernier//fd out reste le meme
	{
		if (p->fd_in_to_use == STDIN_FILENO)
			p->fd_in_to_use = p->fd_in_next;
	}
	else
	{
		if (p->fd_out_to_use == STDOUT_FILENO)
			p->fd_out_to_use = p->fd_tab[1];
		if (p->fd_in_to_use == STDIN_FILENO)
			p->fd_in_to_use = p->fd_in_next;
		p->fd_err_to_use = p->fd_tab_err[1];//
	}
	return (0);
}
