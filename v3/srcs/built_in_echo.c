/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:26:35 by jacher            #+#    #+#             */
/*   Updated: 2021/05/03 22:57:09 by jacher           ###   ########.fr       */
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
	if (i == 0)
		return (0);
	return (1);
}

int		ft_echo(t_simple_cmd *cmd, t_pipe *p, int mod_n, int word)
{
	int		i;

	i = 1;
	while (i < cmd->ac)
	{
		if (cmd->av[i] != NULL)
		{
			if (word == 0 && is_arg_n(cmd->av[i]) == 1)
				mod_n = 1;
			else if (word == 0 && is_arg_n(cmd->av[i]) == 0)
			{
				word = 1;
				ft_putstr_fd(cmd->av[i], p->fd_out_to_use);
			}
			else
			{
				ft_putstr_fd(" ", p->fd_out_to_use);
				ft_putstr_fd(cmd->av[i], p->fd_out_to_use);
			}
		}
		i++;
	}
	if (mod_n == 0)
		ft_putstr_fd("\n", p->fd_out_to_use);
	return (0);
}
