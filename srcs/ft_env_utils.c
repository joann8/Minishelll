/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 18:03:42 by calao             #+#    #+#             */
/*   Updated: 2021/04/16 19:05:18 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		ft_lst_onenv_size(t_list **env)
{
	t_list	*node;
	t_var	*var;
	int		i;

	i = 0;
	node = *env;
	while (node)
	{
		var = (t_var *)(node->content);
		if (var->on)
			i++;
		node = node->next;
	}
	return (i);
}

char	*ft_fuse_var(t_var *var)
{
	char	*str;
	int		len;

	len = ft_strlen(var->name) + ft_strlen(var->value) + 1;
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	ft_strcpy(str, var->name);
	ft_strcat(str, "=");
	ft_strcat(str, var->value);
	return (str);
}

char	**ft_make_ourenvp(t_list **env)
{
	t_var	*var_tmp;
	t_list	*node_tmp;
	int		i;
	char	**our_envp;

	node_tmp = *env;
	i = ft_lst_onenv_size(env);
	if ((our_envp = malloc(sizeof(char *) * (i + 1))) == NULL)
		return (NULL);
	our_envp[i] = NULL;
	i = 0;
	while (node_tmp)
	{
		var_tmp = (t_var *)(node_tmp->content);
		if (var_tmp->on)
		{
			our_envp[i] = ft_fuse_var(var_tmp);
			if (our_envp[i++] == NULL)
				return (free_double_tab(our_envp));
		}
		node_tmp = node_tmp->next;
	}
	return (our_envp);
}




