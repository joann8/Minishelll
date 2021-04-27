/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 13:38:50 by calao             #+#    #+#             */
/*   Updated: 2021/04/27 13:57:14 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	ft_unset_node(t_list **env, t_list *tmp, char *node_name)
{
	t_list	*previous;
	t_var	*v_tmp;

	previous = *env;
	while (previous && previous->next != tmp)
		previous = previous->next;
	if (!previous)
	{
		printf("bash: unset: error while unsetting «%s» node\n", node_name);
		return;
	}
	previous->next = tmp->next;
	v_tmp = (t_var *)(tmp->content);
	free(v_tmp->name);
	free(v_tmp->value);
	free(tmp->content);
	free(tmp);
}

int		ft_unset(t_list **env, char **argv, int pipe_mod, t_list **error)
{
	t_list *tmp;
	int		res;
	
	argv++; // skip le job en ar 1 
	res = 0;
	while (*argv)
	{
		if (is_name(*argv) == 0)
		{
			if (add_err_lst(error, "bash: unset: `", *argv,
					"': not a valid identifier\n") == -1)
				return (-1);
			res = 1;
		}
		else
		{
			if (pipe_mod == 0)
			{
				tmp = ft_lstfind_env(env, *argv, ft_strcmp);
				if (tmp)
					ft_unset_node(env, tmp, *argv);
			}
		}
		argv++;
	}
	return (res);
}
