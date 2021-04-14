/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 14:37:01 by calao             #+#    #+#             */
/*   Updated: 2021/04/14 11:27:06 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"


int		ft_relative_to_absolute(char *exec);
int		ft_path_is_relative(char *str);

t_list	*ft_lstfind_env(t_list *begin, char *content_ref, int (*cmp)())
{
	t_var *tmp;

	while (begin)
	{
		tmp = (t_var *)begin->content;

		if (!((*cmp)(tmp->name, content_ref)))
			return (begin);
		begin = begin->next;
	}
	return (NULL);
}

int		main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	//(void)envp;
	t_list	*env_lst;
	t_list	*tmp;
	t_var	*var;
	char *path;
	char *pwd;

	env_lst = NULL;
	ft_make_envlst(&env_lst, envp);
	ft_print_envlst(env_lst);
	write(1, "la\n", 3);
	tmp = (ft_lstfind_env(env_lst, "PWD", ft_strcmp));
	write(1, "la\n", 3);
	var = (t_var *)(tmp->content);
	write(1, "la\n", 3);
	pwd = var->value;
	printf("pwd = %s\n", pwd);
	while (1)
	{
		ft_get_userinput(&path, pwd);
		ft_relative_to_absolute(path);
	}
	return (0);
}
