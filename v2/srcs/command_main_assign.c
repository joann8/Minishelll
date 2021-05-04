/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_main_assign.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:42:47 by jacher            #+#    #+#             */
/*   Updated: 2021/05/03 23:08:17 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int			check_redir_expansion(t_simple_cmd *cmd, t_redir *r, t_list **env)
{
	char	*new;

	new = modify_str(r->file_name, env);
	if ((is_word(new) == 0 && r->file_name[0] != '"')
			|| ft_strcmp(new, "") == 0)
	{
		cmd->on = 0;
		print_err("msh: ", r->file_name, ": ambiguous redirect\n", 0);
		free(new);
		g_msh.exit_status = 1;
		return (-1);
	}
	else
	{
		free(r->file_name);
		if ((r->file_name = ft_strdup(new)) == NULL)
		{
			free(new);
			return (p_error(0, "malloc error\n", -1));
		}
		free(new);
	}
	return (0);
}

int			assign_list_redir_2(t_redir *r, t_simple_cmd *cmd)
{
	if (r->e_type == OUT)
	{
		if (cmd->fd_out > 1)
			close(cmd->fd_out);
		cmd->fd_out = open(r->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		if (cmd->fd_out < 0)
			return (print_err(strerror(errno), NULL, NULL, 0));
	}
	else if (r->e_type == APPEND)
	{
		if (cmd->fd_out > 1)
			close(cmd->fd_out);
		cmd->fd_out = open(r->file_name, O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (cmd->fd_out < 0)
			return (print_err(strerror(errno), NULL, NULL, 0));
	}
	return (0);
}

int			assign_list_redir(t_list *tmp_l, t_simple_cmd *cmd, t_list **env)
{
	t_redir	*r;

	g_msh.exit_status = 0;
	while (tmp_l)
	{
		r = (t_redir *)tmp_l->content;
		if (check_redir_expansion(cmd, r, env) == -1)
			return (0);
		if (r->e_type == IN)
		{
			if (cmd->fd_in > 0)
				close(cmd->fd_in);
			if ((cmd->fd_in = open(r->file_name, O_RDONLY)) < 0)
			{
				cmd->on = 0;
				g_msh.exit_status = 1;
				print_err("msh : ", r->file_name, ": ", 0);
				return (print_err(strerror(errno), "\n", NULL, 0));
			}
		}
		else if (assign_list_redir_2(r, cmd) == -1)
			return (p_error(0, "malloc error\n", -1));
		tmp_l = tmp_l->next;
	}
	return (0);
}

int			assign_list_word(t_seq *seq, t_simple_cmd *cmd, t_list **env)
{
	int		i;
	char	*new;
	t_list	*tmp;

	tmp = seq->word;
	i = 0;
	while (tmp)
	{
		if (tmp->content)
		{
			if (i == 0)
				if ((cmd->job = ft_strdup((char *)tmp->content)) == NULL)
					return (p_error(0, "malloc error\n", -1));
			if ((new = modify_str((char*)tmp->content, env)) == NULL)
				return (p_error(0, "malloc error\n", -1));
			if (assign_cmd_av(cmd, tmp, new, i) == -1)
				return (-1);
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
	if (seq->pipe_pos == seq->pipe_total)
		cmd->pipe_pos = 1;
	else if (seq->pipe_pos == 0)
		cmd->pipe_pos = -1;
	else
		cmd->pipe_pos = 0;
}
