/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:37:01 by calao             #+#    #+#             */
/*   Updated: 2021/04/13 20:12:01 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"


int		ft_relative_to_absolute(char *exec);

int		main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	char *exec;

	exec = av[1];
	ft_relative_to_absolute(exec);
	return (0);
}
