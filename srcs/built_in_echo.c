/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:26:35 by jacher            #+#    #+#             */
/*   Updated: 2021/04/16 22:45:58 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		is_arg_n(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && str[i] == '-')
			i++;
		else if (str[i] == 'n')
			i++;
		else 	
			return (0);
	}
	return (1);
}

int		ft_echo(t_simple_cmd *cmd, t_pipe *p)
{
	int		mod_n;
	int		word;
	int		i;

// Y'a t'il des erreurs a gérer?? 
	mod_n = 0;
	word = 0;
	i = 1;
	while (cmd->av[i])
	{
		if (word == 0)
		{
			if (is_arg_n(cmd->av[i]) == 1)
				mod_n = 1;
			else
			{
				word = 1;
				write(p->fd_out_to_use, cmd->av[i], ft_strlen(cmd->av[i]));
			}
		}
		else
		{
			write(p->fd_out_to_use, " ", 1);
			write(p->fd_out_to_use, cmd->av[i], ft_strlen(cmd->av[i]));
		}
		i++;
	}
	if (mod_n == 0)
		write(p->fd_out_to_use, "\n", 1);
	g_gnl.exit_status = 1;
	//EXIT SUCCESS TO REGISTER
	return (1);
}
