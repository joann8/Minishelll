/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 13:38:50 by calao             #+#    #+#             */
/*   Updated: 2021/05/02 21:36:47 by calao            ###   ########.fr       */
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
		return ;
	previous->next = tmp->next;
	v_tmp = (t_var *)(tmp->content);
	free(v_tmp->name);
	free(v_tmp->value);
	free(tmp->content);
	free(tmp);
}

int		ft_unset(t_simple_cmd *cmd, t_list **env, char **argv)
{
	t_list	*tmp;
	int		res;
	int		i;

	res = 0;
	i = 1;
	while (i < cmd->ac)
	{
		if (argv[i] != NULL && ft_check_export_name(argv[i]) == 0)
		{
			print_err("msh: unset: `", argv[i]
					, "': not a valid identifier\n", 1);
			res = 1;
		}
		else if (argv[i] != NULL)
		{
			tmp = ft_lstfind_env(env, argv[i], ft_strcmp);
			if (tmp)
				ft_unset_node(env, tmp);
		}
		i++;
	}
	return (res);
}
