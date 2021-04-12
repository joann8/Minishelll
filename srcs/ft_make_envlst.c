/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_envlst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:49:33 by calao             #+#    #+#             */
/*   Updated: 2021/04/12 10:03:49 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

char	*ft_getenv_name(char *env_str)
{
	int		len;
	char	*name;

	len = 0;
	while (env_str[len] != '=' && env_str[len])
		len++;
	name = malloc(sizeof(*name) * (len + 1));
	if (name == NULL)
		return (name);
	ft_strncpy(name, env_str, len);
	return (name);
}


int		ft_make_envlst(t_list **head, char **envp)
{
	t_list	*new_node;
	t_var	*my_env;
	int		i;

	i = 0;
	new_node = NULL;
	while (*envp)
	{
		my_env = malloc(sizeof(*my_env));
		if (my_env == NULL)
			return (-1);
		// erreur possible dans ces fonctions ?
		my_env->name = ft_getenv_name(*envp);
		if (my_env->name == NULL)
			return (-1);
		my_env->value = ft_strdup(getenv(my_env->name));
		if (my_env->value == NULL)
			return (-1);
		new_node = ft_lstnew(my_env);
		if (new_node == NULL)
			return (-1);
		ft_lstadd_back(head, new_node);
		i++;
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
		//printf("name=%s\n", var->name);
		free(var->name);
		free(var->value);
		free(tmp->content);
		free(tmp);
		tmp = next;
	}

}
