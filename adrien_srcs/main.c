/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:37:01 by calao             #+#    #+#             */
/*   Updated: 2021/04/09 15:55:47 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		ft_main_history(void);

int		main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_list *env_lst;
	env_lst = NULL;
	ft_make_envlst(&env_lst, envp);
	printf("ok\n");
	ft_print_envlst(env_lst);
	ft_main_history();
	return (0);
}
