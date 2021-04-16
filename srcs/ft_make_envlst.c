/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_envlst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:49:33 by calao             #+#    #+#             */
/*   Updated: 2021/04/16 22:20:44 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

char	*ft_getenv_name(char *env_str)
{
	int		len;
	char	*name;

	len = 0;
	if (env_str == NULL)
		return (NULL);
	while (env_str[len] && env_str[len] != '=')
		len++;
	name = malloc(sizeof(char) * (len + 1));
	if (name == NULL)
		return (NULL);
	ft_strncpy(name, env_str, len);
	return (name);
}


int		ft_make_envlst(t_list **head, char **envp)
{
	t_list	*new_node;
	t_var	*my_env;

	new_node = NULL;
	while (*envp)
	{
		my_env = malloc(sizeof(*my_env));
		if (my_env == NULL)
			return (-1);
		my_env->name = NULL;
		my_env->value = NULL;
		my_env->on = -1;
		// erreur possible dans ces fonctions ?
		my_env->name = ft_getenv_name(*envp);
		if (my_env->name == NULL)
			return (-1);
		my_env->value = ft_strdup(getenv(my_env->name));
		if (my_env->value == NULL)
			return (-1);
		my_env->on = 1;
		new_node = ft_lstnew(my_env);
		if (new_node == NULL)
			return (-1);
		ft_lstadd_back(head, new_node);
		envp++;
	}
	return (0);
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
		/*if (!tmp->name)
			tmp->name = "";
			*/
		if (!((*cmp)(tmp->name, content_ref)))
			return (cur);
		cur = cur->next;
	}
	return (NULL);
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
		/*if (!tmp->name)
			tmp->name = "";
		*/
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
