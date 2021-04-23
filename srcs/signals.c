/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 18:39:18 by jacher            #+#    #+#             */
/*   Updated: 2021/04/21 11:36:15 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	reading_sigint(int sig)
{
	ft_putstr_fd("\n", 1);
	g.exit_status = 130;
	//print prompt	
	
	/*else if (g.shell_level == 0)
	{
		g.exit_status = 1;
		ft_putstr_fd("chelou", 1);
	}*/
	return;
}

void	reading_sigquit(int sig)
{
	ft_putstr_fd(1, "\b\b \b\b");
}

void	exec_sigint(int sig)
{
	kill(0 , sig);//kill child;
	//kill(g.pid[0], sig);//kill child 
	//kill(g.pid[1], sig);//kill parent
	g.exit_status = 130;
	ft_putstr_fd("\n", 1);

	/*else if (g.shell_level == 0)
	{
		g.exit_status = 1;
		ft_putstr_fd("chelou", 1);
	}*/
}

void	exec_sigquit(int sig)
{
	kill(0 , sig);//kill child parent;
	//kill(g.pid[0], sig);//kill child process;
	//kill(g.pid[1], sig);//kill child process;
	g_gnl.exit_status = 131;
	ft_putstr_fd(1, "Quit (core dumped)\n");
}
	
void	reading_listen_signal(void)
{
	signal(SIGINT, reading_sigint);//quand on tape clc c (SIGINT), lance manage c 
	signal(SIGQUIT, reading_sigquit);//quand on tape clt \, SIG QUIT on lance manage slash >> pgm terminates anc cor dump core
//	Quit (core dumped)
}

void	exec_listen_signal(void)
{
	signal(SIGINT, exec_sigint);//quand on tape clc c (SIGINT), lance manage c 
	signal(SIGQUIT, exec_sigquit);//quand on tape clt \, SIG QUIT on lance manage slash >> pgm terminates anc cor dump core
//	Quit (core dumped)
}
