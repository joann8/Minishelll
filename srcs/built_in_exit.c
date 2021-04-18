/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:26:23 by jacher            #+#    #+#             */
/*   Updated: 2021/04/17 17:29:21 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		ft_exit(t_simple_cmd *cmd, t_pipe *p)
{
	int i;

	ft_putstr_fd("exit\n", p->fd_out_to_use);
	if (cmd->ac > 1)
	{
		i = 0;
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
				ft_putstr_fd("msh : exit: ", p->fd_out_to_use);
				ft_putstr_fd(cmd->av[1], p->fd_out_to_use);
				ft_putstr_fd(" : argument numérique nécessaire\n", p->fd_out_to_use);
				g_process.exit_status = 2;
				return (g_process.exit_status);//error code
			}
		}
		if (cmd->ac > 2)
		{
			ft_putstr_fd("msh : exit: trop d'arguments.\n", p->fd_out_to_use);
			g_process.exit_status = 131; //a verifier, equivalent -1
			return (g_process.exit_status);
		}
		g_process.exit_status = ft_atoi(cmd->av[1]);
	}
	else
		g_process.exit_status = 0;
	return (g_process.exit_status); //cas par défaut : returned last exit code
}
