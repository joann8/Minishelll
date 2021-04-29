/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:37:01 by calao             #+#    #+#             */
/*   Updated: 2021/04/29 12:01:27 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	read_ctrl_c(int signum)
{
	(void)signum;
	close(g.fd);
	g.exit_status = 130;
	write(1, "^C\n", 3);
}

void	read_ctrl_quit(int signum)
{
	(void)signum;
	//g.exit_status = 131;
}

void	exec_ctrl_c(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	g.exit_status = 130;
}

void	exec_ctrl_quit(int signum)
{
	(void)signum;
	ft_putstr_fd("Quit (core dumped)\n", 1);
	g.exit_status = 131;
}
