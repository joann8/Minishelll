/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:28:48 by jacher            #+#    #+#             */
/*   Updated: 2021/04/16 10:47:14 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		find_built_in(t_simple_cmd *cmd, t_pipe *p)
{
	if (ft_strcmp(cmd->job, "echo") == 0)
	{
		printf("ECHO FOUND!\n");
		ft_echo(cmd, p);
		return (1);
	}
/*	if (ft_strcmp(cmd->job, "cd") == 0)
		return (2);
	if (ft_strcmp(cmd->job, "pwd") == 0)
		return (3);
	if (ft_strcmp(cmd->job, "export") == 0)
		return (4);
	if (ft_strcmp(cmd->job, "unset") == 0)
		return (5);
	if (ft_strcmp(cmd->job, "env") == 0)
		return (6);
	if (ft_strcmp(cmd->job, "exit") == 0)
		return (7);*/
	return (0);
}
