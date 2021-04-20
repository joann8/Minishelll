/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pipe_assign.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:42:47 by jacher            #+#    #+#             */
/*   Updated: 2021/04/20 19:18:16 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int			assign_list_redir_2(t_redir *r, t_simple_cmd *cmd, t_list **error)
{
	if (r->e_type == OUT)
	{
		if (cmd->fd_out > 1)
			close(cmd->fd_out);//essayer READ ? QUID si c'est un dossier ?
		cmd->fd_out = open(r->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0664);//664 a checker
		if (cmd->fd_out < 0)
		{
			if (add_err_lst(error, strerror(errno), NULL, NULL) == -1)
				return (-1);
			return (1);//inutile?
		}
	}
	else if (r->e_type == APPEND)
	{
		if (cmd->fd_out > 1)
			close(cmd->fd_out);//essayer de READ ? QUID si c'est un dossier ?
		cmd->fd_out = open(r->file_name, O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (cmd->fd_out < 0)
		{
			if (add_err_lst(error, strerror(errno), NULL, NULL) == -1)
				return (-1);
			return (1);//inutile?
		}
	}
	return (0);
}

int			assign_list_redir(t_list *tmp_l, t_simple_cmd *cmd, t_list **error)
{
	t_redir	*r;

	while (tmp_l)
	{
		r = (t_redir *)tmp_l->content;
		if (r->e_type == IN)
		{
			if (cmd->fd_in > 0)
				close(cmd->fd_in);//essayer de READ ? QUID si c'est un dossier?
			cmd->fd_in = open(r->file_name, O_RDONLY);
			if (cmd->fd_in < 0)
			{
				if (add_err_lst(error, "msh : ", r->file_name, ": ") == -1
					|| add_err_lst(error, strerror(errno), "\n", NULL) == -1)//checker pour le retour a la ligne
					return (p_error(0, "malloc error\n", -1));
				cmd->on = 0;//pipe ne s'executera pas
				g_process.exit_status = 1;
			}
		}
		else if (assign_list_redir_2(r, cmd, error) == -1)
			return (p_error(0, "malloc error\n", -1));
		tmp_l = tmp_l->next;
	}
	return (0);
}

int			assign_list_word(t_seq *seq, t_simple_cmd *cmd)
{
	int		i;
	t_list	*tmp;

	tmp = seq->word;
	i = 0;
	while (tmp)
	{
		if (i == 0)//error opening with wrong rights
		{
			cmd->job = ft_strdup((char *)tmp->content);
			if (cmd->job == NULL)
				return (p_error(0, "malloc error\n", -1));
		}
		cmd->av[i] = ft_strdup(tmp->content);//recheker ce qu'il faut free ou pas
		if (cmd->av[i] == NULL)//erreur malloc
		{
			free(cmd->job);
			return (p_error(0, "malloc error\n", -1));
		}
		tmp = tmp->next;
		i++;
	}
	cmd->av[i] = NULL;
	return (0);
}

void		assign_pipes(t_seq *seq, t_simple_cmd *cmd)
{
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	if (seq->pipe_total > 0)
		cmd->pipe_mod = 1;
	else
		cmd->pipe_mod = 0;
	if (seq->pipe_pos == seq->pipe_total)
		cmd->pipe_pos = 1;
	else if (seq->pipe_pos == 0)
		cmd->pipe_pos = -1;
	else
		cmd->pipe_pos = 0;
}
