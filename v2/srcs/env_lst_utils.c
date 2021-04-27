/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 18:03:42 by calao             #+#    #+#             */
/*   Updated: 2021/04/27 22:38:03 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

t_list	*ft_env_node_copy(t_var *v_src)
{
	t_list	*new;
	t_var	*v_dst;
	
	if ((new = ft_lstnew(NULL)) == NULL)
			return (NULL);
	if ((new->content = malloc(sizeof(t_var))) == NULL)
	{
		free(new);
		return (NULL);
	}
	v_dst = (t_var *)(new->content);
	if ((v_dst->name = ft_strdup(v_src->name)) == NULL)
	{
		free(new->content);
		free(new);
		return (NULL);
	}
	if ((v_dst->value = ft_strdup(v_src->value)) == NULL)
	{
		free(v_dst->name);
		free(new->content);
		free(new);
		return (NULL);
	}
	return (new);
}

int		ft_lst_env_copy(t_list **dest, t_list **src)
{
	t_var	*v_src;
	t_var	*v_dst;
	t_list	*tmp;
	t_list	*new;

	tmp = *src;
	while (tmp)
	{
		v_src = (t_var *)(tmp->content);
		if (ft_strcmp(v_src->name, "_") != 0)
		{
			new = ft_env_node_copy(v_src);
			if (new == NULL)
				return (-1);
			v_dst = (t_var *)new->content;
			v_dst->on = v_src->on;
			ft_lstadd_back(dest, new);
		}
		tmp = tmp->next;
	}
	return (0);
	//SUPPRIMER le dernier noeud ? _=./minishell pour export ???
}

void	ft_lst_env_sort(t_list **begin, int (*cmp)())
{
	t_list	*current;
	t_list	*next;
	t_var	*v_cur;
	t_var	*v_next;

	current = *begin;
	while (current)
	{
		next = current->next;
		while (next)
		{
			v_cur = (t_var *)current->content;
			v_next = (t_var *)next->content;
			if ((*cmp)(v_cur->name, v_next->name) > 0)
				ft_swap_content(current, next);
			next = next->next;
		}
		current = current->next;
	}
}

void	ft_lstclear_envlst(t_list **head)
{
	t_list *tmp;
	t_list *next;
	t_var	*var;

	if (!head || !*head)
		return;
	tmp = *head;
	while (tmp)
	{
		next = tmp->next;
		var = (t_var*)(tmp->content);
		if (var)
		{
			if (var->name)
				free(var->name);
			if (var->value)
				free(var->value);
			free(var);
		}
		free(tmp);
		tmp = next;
	}
}

t_list	*ft_lstfind_env(t_list **begin, char *content_ref, int (*cmp)())
{
	t_var *tmp;
	t_list *cur;

	if (!begin || !*begin)
		return (NULL);
	cur = *begin;
	while (cur)
	{
		tmp = (t_var *)(cur->content);
		if (((*cmp)(tmp->name, content_ref)) == 0)
		{
			if (tmp->on == 1)
				return (cur);
			else
				return (NULL);
		}
		cur = cur->next;
	}
	return (NULL);
}
