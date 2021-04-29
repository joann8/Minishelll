/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 18:39:18 by jacher            #+#    #+#             */
/*   Updated: 2021/04/29 11:26:32 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	reading_sigint(int sig)
{
	ft_putstr_fd("\n", 1);
	g.exit_status = 130;
}

void	reading_sigquit(int sig)
{
	ft_putstr_fd(1, "\b\b \b\b");
}

void	exec_sigint(int sig)
{
	kill(0, sig);
	g.exit_status = 130;
	ft_putstr_fd("\n", 1);
}

void	exec_sigquit(int sig)
{
	kill(0, sig);
	g_gnl.exit_status = 131;
	ft_putstr_fd(1, "Quit (core dumped)\n");
}

void	reading_listen_signal(void)
{
	signal(SIGINT, reading_sigint);
	signal(SIGQUIT, reading_sigquit);
}

void	exec_listen_signal(void)
{
	signal(SIGINT, exec_sigint);
	signal(SIGQUIT, exec_sigquit);
}
