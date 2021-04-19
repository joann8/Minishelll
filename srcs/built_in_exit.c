/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:26:23 by jacher            #+#    #+#             */
/*   Updated: 2021/04/19 21:57:09 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		ft_exit(t_simple_cmd *cmd, t_pipe *p)
{
	int i;
	unsigned char c;

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
				return (2);//error code
			}
		}
		if (cmd->ac > 2)
		{
			ft_putstr_fd("msh : exit: trop d'arguments.\n", p->fd_out_to_use);
			return (131);//a verifier, equivalent -1

		}
		c = ft_atoi(cmd->av[1]);
		return (c);
	}
	return (0); //cas par défaut : returned last exit code
}
