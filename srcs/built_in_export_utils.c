/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 16:58:35 by calao             #+#    #+#             */
/*   Updated: 2021/04/22 16:33:05 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

t_var	*ft_allocate_env_var_struct_2(char *argv, int i, int j, t_var *v_tmp)
{
		v_tmp->value = ft_strndup(argv + i, j);
		if (v_tmp->value == NULL)
		{
			free(v_tmp);
			free(v_tmp->name);
			return (NULL);
		}
		v_tmp->on = 1;
		return (v_tmp);
}

t_var	*ft_allocate_env_var_struct(char *argv, int i, int j, int mode)
{
	t_var *v_tmp;

	v_tmp = malloc(sizeof(t_var *));
	if (v_tmp == NULL)
		return (NULL);
	v_tmp->value = NULL;
	v_tmp->on = 0;
	if (mode == 1)
		v_tmp->name = ft_strdup(argv);
	else
		v_tmp->name = ft_strndup(argv, i - 1);
	if (v_tmp->name == NULL)
	{
		free(v_tmp);
		return (NULL);
	}
	if (mode == 1)
	{
		v_tmp->value = ft_strdup("");
		if (v_tmp->value == NULL)
		{
			free(v_tmp->name);
			free(v_tmp);
			return (NULL);
		}
	}
	else
		return (ft_allocate_env_var_struct_2(argv, i, j, v_tmp));
	return (v_tmp);
}

t_list	*ft_allocate_env_node(char *argv, int i, int j, int mode)
{
	t_list	*new;

	new = ft_lstnew(NULL);
	if (new == NULL)
		return (NULL);
	new->content = (void *)ft_allocate_env_var_struct(argv, i, j, mode);
	if (new->content == NULL)
	{
		free(new);
		return (NULL);
	}
		return (new);
}
	

int		ft_lst_env_addback(t_list **env, char *argv)
{
	int		i;
	int		j;
	int		mode;
	t_list	*new_node;

	i = 0;
	mode = 1;
	j = 0;
	while (argv[i] && argv[i] != '=')
		i++;
	if (argv[i] == '=')
	{
		i++;
		mode = 2;
		while (argv[i + j])
			j++;
	}
	new_node = ft_allocate_env_node(argv, i, j, mode);
	if (new_node == NULL)
		return (-1);
	ft_lstadd_back(env, new_node);
	return (0);
}

t_list	*ft_lstfind_export(t_list **begin, char *content_ref, int (*cmp)())
{
	t_var *tmp;
	t_list *cur;

	if (!begin || !*begin)
		return (NULL);

	cur = *begin;
	while (cur)
	{
		tmp = (t_var *)(cur->content);
		if (!((*cmp)(tmp->name, content_ref)))
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}
