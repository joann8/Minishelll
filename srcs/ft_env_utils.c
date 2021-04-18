/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 18:03:42 by calao             #+#    #+#             */
/*   Updated: 2021/04/17 17:50:06 by calao            ###   ########.fr       */
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
		new = ft_env_node_copy(v_src);
		if (new == NULL)
			return (-1);
		v_dst = (t_var *)new->content;
		v_dst->on = v_src->on;
		ft_lstadd_back(dest, new);
		tmp = tmp->next;
	}
	return (0);
	//SUPPRIMER le dernier noeud ? _=./minishell pour export ???
}

void	ft_swap_content(t_list *a, t_list *b)
{
	void	*tmp;

	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
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
