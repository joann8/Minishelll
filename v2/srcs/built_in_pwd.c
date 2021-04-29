/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:54:26 by jacher            #+#    #+#             */
/*   Updated: 2021/04/29 10:53:51 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		ft_pwd(t_pipe *p)
{
	char	*to_write;
	to_write = getcwd(NULL, 0);
	if (to_write == NULL)
	{
		print_err("msh : pwd: getcwd failed\n", NULL, NULL, 1);
		return (-1);
		// Ancienne version de Joann -> return (1);// pas sure que l'on doit quit
	}
	ft_putstr_fd(to_write, p->fd_out_to_use);
	ft_putstr_fd("\n", p->fd_out_to_use);
	free(to_write);
	return (0);
}
