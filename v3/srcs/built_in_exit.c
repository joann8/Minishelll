/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:26:23 by jacher            #+#    #+#             */
/*   Updated: 2021/05/04 10:48:27 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		ft_exit_help(t_simple_cmd *cmd, int i)
{
	while (cmd->av[1][i])
	{
		if (i == 0)
		{
			if (cmd->av[1][0] == '-' || cmd->av[1][0] == '+')
				i++;
		}
		if (ft_isdigit(cmd->av[1][i]) == 1)
			i++;
		else
		{
			print_err("msh: exit: ", cmd->av[1],
					" : numeric argument required\n", 0);
			return (2);
		}
	}
	if (cmd->ac > 2)
	{
		print_err("msh : exit: too many arguments\n",
			NULL, NULL, 0);
		return (1);
	}
	return (0);
}

int		ft_exit(t_simple_cmd *cmd, t_pipe *p)
{
	int				res;
	unsigned char	c;

	if (cmd->pipe_pos == -2)
		ft_putstr_fd("exit\n", p->fd_out_to_use);
	if (cmd->ac > 1)
	{
		res = ft_exit_help(cmd, 0);
		if (res != 0)
			return (res);
		c = ft_atoi(cmd->av[1]);
		return (c);
	}
	return (0);
}
