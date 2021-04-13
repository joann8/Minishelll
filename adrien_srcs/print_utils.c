/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:56:23 by calao             #+#    #+#             */
/*   Updated: 2021/04/13 18:49:54 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	ft_puttab(char **av)
{
	while (*av)
	{
		ft_putstr(*av);
		ft_putchar('\n');
		av++;
	}
}
void	ft_print_str_lst(t_list *head)
{
	t_list *tmp;

	tmp = head;
	while (tmp)
	{
		printf("[%s] --> ", (char *)tmp->content);
		tmp = tmp->next;
	}
	printf("\n");
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

