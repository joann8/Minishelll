/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:26:35 by jacher            #+#    #+#             */
/*   Updated: 2021/04/15 16:12:27 by jacher           ###   ########.fr       */
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

void	ft_echo(t_simple_cmd *cmd)
{
	int		mod_n;
	int		word;
	int		i;

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
				write(cmd->fd_out, cmd->av[i], ft_strlen(cmd->av[i]));
			}
		}
		else
		{
			write(cmd->fd_out, " ", 1);
			write(cmd->fd_out, cmd->av[i], ft_strlen(cmd->av[i]));
		}
		i++;
	}
	if (mod_n == 0)
		write(cmd->fd_out, "\n", 1);
}


