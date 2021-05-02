/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:00:18 by jacher            #+#    #+#             */
/*   Updated: 2021/05/02 12:09:42 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	ft_free_cmd_av_tab(char **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

void	ft_free_command_list(t_simple_cmd *cmd_list)
{
	t_simple_cmd	*tmp;
	t_simple_cmd	*previous;

	tmp = cmd_list;
	while (tmp)
	{
		if (tmp->job)
			free(tmp->job);
		if (tmp->av)
			ft_free_cmd_av_tab(tmp->av);
		previous = tmp;
		tmp = tmp->next_pipe;
		free(previous);
	}
}

void	ft_free_command(t_list *cmd_list)
{
	t_list			*tmp;
	t_simple_cmd	*cmd;

	tmp = cmd_list;
	while (tmp)
	{
		cmd = (t_simple_cmd *)tmp->content;
		if (cmd->job)
			free(cmd->job);
		if (cmd->av)
			ft_free_cmd_av_tab(cmd->av);
		tmp = tmp->next;
	}
}
