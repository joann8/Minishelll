/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:37:01 by calao             #+#    #+#             */
/*   Updated: 2021/04/13 12:42:03 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"


char	*ft_find_cmd_path(char *exec);

int		main(int ac, char **av, char **envp)
{
	(void)ac;
	char *exec;
	//char *arg[3];
	//arg = "." ;
	/*char	*line;
	t_list	*env_lst;

	env_lst = NULL;
	ft_make_envlst(&env_lst, envp);
	ft_print_envlst(env_lst);
	ft_get_userinput(&line);
	ft_lstclear_envlst(&env_lst);
	free(line);
	*/
	//arg[0] = "ls";
	//arg[1] = ".";
	//arg[2] = NULL;
	(void)envp;

	exec = ft_find_cmd_path(av[1]);
	if (exec == NULL)
	{
		printf("command not found\n");
		return (1);
	}
	printf("avant execve :[%s]\n", exec);
	printf("ret = %d\n", execlp(exec, "ls", NULL));
	printf("apres execve :[%s]\n", exec);
	
	return (0);
}
