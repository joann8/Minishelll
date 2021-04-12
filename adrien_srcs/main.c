/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:37:01 by calao             #+#    #+#             */
/*   Updated: 2021/04/12 23:00:15 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"


char	*ft_find_cmd_path(char *exec);

int		main(int ac, char **av, char **envp)
{
	(void)ac;
	char *exec;
	char *arg[2];
	/*char	*line;
	t_list	*env_lst;

	env_lst = NULL;
	ft_make_envlst(&env_lst, envp);
	ft_print_envlst(env_lst);
	ft_get_userinput(&line);
	ft_lstclear_envlst(&env_lst);
	free(line);
	*/
	arg[0] = "";
	arg[2] = NULL;
	exec = ft_find_cmd_path(av[1]);
	execve(exec, arg, envp);
	return (0);
}
