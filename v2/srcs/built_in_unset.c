/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 13:38:50 by calao             #+#    #+#             */
/*   Updated: 2021/04/28 10:15:45 by calao            ###   ########.fr       */
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
		return;
	previous->next = tmp->next;
	v_tmp = (t_var *)(tmp->content);
	free(v_tmp->name);
	free(v_tmp->value);
	free(tmp->content);
	free(tmp);
}

int		ft_unset(t_list **env, char **argv)
{
	t_list *tmp;
	int		res;
	
	argv++; // skip le job en ar 1 
	res = 0;
	while (*argv)
	{
		if (ft_check_export_name(*argv) == 0)
		{
			print_err("msh: unset: `", *argv
					, "': not a valid identifier\n", 1);
			res = 1;
		}
		else
		{
			tmp = ft_lstfind_env(env, *argv, ft_strcmp);
			if (tmp)
				ft_unset_node(env, tmp);
		}
		argv++;
	}
	return (res);
}
