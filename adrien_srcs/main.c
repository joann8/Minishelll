/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:18:29 by calao             #+#    #+#             */
/*   Updated: 2021/04/09 14:29:50 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"
// s_var
// char *name
// char *value;
// t_var

int		ft_make_envlst(t_list **head, char **envp);
void	ft_print_envlst(t_list *env);

void	ft_print_str_av(char **av)
{
	while (*av)
	{
		ft_putstr(*av);
		ft_putchar('\n');
		av++;
	}
}

int		main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_list *env_root;
	
	//ft_print_str_av(envp);
	env_root = NULL;
	ft_make_envlst(&env_root, envp);
	ft_print_envlst(env_root);
	
	return (0);
	/* Minishell input
	char *line;
	if (!ft_get_userinput(&line))
		return (1);
	printf("Full command = \"%s\"\n", line);
	*/
}

void	ft_print_envlst(t_list *env_head)
{
	t_var	*var;
	t_list	*tmp;

	tmp = env_head;
	while (tmp)
	{
		var = (t_var*)(tmp->content);
		printf("%s=%s\n", var->name, var->value);
		tmp = tmp->next;
	}
}
