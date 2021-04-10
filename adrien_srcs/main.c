/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:37:01 by calao             #+#    #+#             */
/*   Updated: 2021/04/10 09:34:14 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		ft_make_loglst(t_list **log, int fd);
void	ft_print_str_lst(t_list *head);

int		main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	int		fd_log;
	char	*line;
	t_list	*env_lst;
	t_list	*log_lst;


	env_lst = NULL;
	log_lst = NULL;
	ft_make_envlst(&env_lst, envp);
	printf("ok\n");
	ft_print_envlst(env_lst);
	fd_log = open("minishell.log", O_RDWR | O_CREAT | O_APPEND, 0666);
	if (fd_log < 0)
		return (-1);
	
	ft_make_loglst(&log_lst, fd_log);
	ft_get_userinput(fd_log, &line, log_lst);
	close(fd_log);
	return (0);
}
