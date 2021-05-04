/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:37:01 by calao             #+#    #+#             */
/*   Updated: 2021/05/04 10:01:08 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	read_ctrl_c(int signum)
{
	(void)signum;
	close(g_msh.fd);
	g_msh.exit_status = 130;
	write(1, "^C\n", 3);
}

void	read_ctrl_quit(int signum)
{
	(void)signum;
}

void	exec_ctrl_c(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	g_msh.exit_status = 130;
}

void	exec_ctrl_quit(int signum)
{
	(void)signum;
	ft_putstr_fd("Quit (core dumped)\n", 1);
	g_msh.exit_status = 131;
}

void	listen_signals(char c)
{
	if (c == 'r')
	{
		signal(SIGINT, read_ctrl_c);
		signal(SIGQUIT, read_ctrl_quit);
	}
	if (c == 'e')
	{
		signal(SIGINT, exec_ctrl_c);
		signal(SIGQUIT, exec_ctrl_quit);
	}
}
