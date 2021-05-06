/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_builder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:49:33 by calao             #+#    #+#             */
/*   Updated: 2021/04/20 16:38:27 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		setup_var_name_and_value(char *env_str, t_var *my_env)
{
	int		len;

	len = 0;
	while (env_str[len] && env_str[len] != '=')
		len++;
	my_env->name = ft_strndup(env_str, len);
	if (my_env->name == NULL)
		return (-1);
	my_env->value = ft_strdup(getenv(my_env->name));
	if (my_env->value == NULL)
		return (-1);
	return (0);
}

char	*ft_getenv_name(char *env_str)
{
	int		len;
	char	*name;

	len = 0;
	while (env_str[len] && env_str[len] != '=')
		len++;
	name = ft_strndup(env_str, len);
	if (name == NULL)
		return (NULL);
	return (name);
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
	i = ft_lst_on_env_size(env);
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
			if (our_envp[i] == NULL)
				return (free_double_tab(our_envp));
			i++;
		}
		node_tmp = node_tmp->next;
	}
	return (our_envp);
}

int		ft_make_envlst(t_list **head, char **envp)
{
	t_list	*new_node;
	t_var	*my_env;

	new_node = NULL;
	while (*envp)
	{
		new_node = ft_lstnew(NULL);
		if (new_node == NULL)
			return (-1);
		ft_lstadd_back(head, new_node);
		my_env = malloc(sizeof(*my_env));
		if (my_env == NULL)
			return (-1);
		new_node->content = my_env;
		my_env->name = NULL;
		my_env->value = NULL;
		if (setup_var_name_and_value(*envp, my_env) == -1)
			return (-1);
		my_env->on = 1;
		envp++;
	}
	return (0);
}
