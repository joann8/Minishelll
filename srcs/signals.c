/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 18:39:18 by jacher            #+#    #+#             */
/*   Updated: 2021/04/16 18:50:38 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	manage_c
{
	if (jjjjj)
	{
		kill(0, sig);//kill child process;
		//kill parent?
		g_gnl.exit_status = 130;
		ft_putstr_fd(2, "\n");
	}
	else if (g_gnl.shell_level == 0)
	{
		g_gnl.exit_status = 1;
		ft_putstr_fd("chelou", 1);
	}
}



void	manage_slash(int sig)
{
	kill(0, sig);//kill child process;
	//kill parent?
	g_gnl.exit_status = 131;
	ft_putstr_fd(2, "Quit: 3\n");
}
	
void	listen_signal(void)
{
	signal(SIGINT, manage_c);
	signal(SIGQUIT, manage_slash);
}
