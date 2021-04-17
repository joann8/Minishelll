/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 13:38:50 by calao             #+#    #+#             */
/*   Updated: 2021/04/17 15:05:10 by calao            ###   ########.fr       */
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

int		ft_unset(t_list **env, char **argv)
{
	t_list *tmp;
	char *str;
	str = "\n\tTTTTTT____enter UNSET____TTTTTTT\n";
	write(1, str, ft_strlen(str));
	argv++; // skip le job en ar 1 
	while (*argv)
	{
		if (!is_name(*argv))
		{
			//Ecrire dans le stderr
			printf("bash: unset: `%s': not a valid identifier\n", *argv);
		}
		else
		{
			tmp = ft_lstfind_env(env, *argv, ft_strcmp);
			if (tmp)
				ft_unset_node(env, tmp);
		}
		argv++;
	}
	return (1);
}
