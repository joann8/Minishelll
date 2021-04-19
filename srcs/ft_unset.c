/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 13:38:50 by calao             #+#    #+#             */
/*   Updated: 2021/04/19 22:04:06 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	ft_unset_node(t_list **env, t_list *tmp)
{
	t_list	*previous;
	t_var	*v_tmp;

	previous = *env;
	while (previous && previous->next != tmp)
		previous = previous->next;
	if (!previous)
	{
		printf("err in unset node\n");
		return;
	}
	previous->next = tmp->next;
	v_tmp = (t_var *)(tmp->content);
	free(v_tmp->name);
	free(v_tmp->value);
	free(tmp->content);
	free(tmp);
}

int		ft_unset(t_list **env, char **argv, int pipe_mod)
{
	t_list *tmp;
	int		res;
	
	argv++; // skip le job en ar 1 
	res = 0;
	while (*argv)
	{
		printf("argv = %s\n", *argv);
		if (is_name(*argv) == 0)
		{
			//Ecrire dans le stderr
			printf("bash: unset: `%s': not a valid identifier\n", *argv);
			res = 1;
		}
		else
		{
			if (pipe_mod == 0)
			{
				tmp = ft_lstfind_env(env, *argv, ft_strcmp);
				if (tmp)
					ft_unset_node(env, tmp);
			}
		}
		argv++;
	}
	return (res);
}
