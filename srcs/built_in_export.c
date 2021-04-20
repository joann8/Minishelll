/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 16:58:35 by calao             #+#    #+#             */
/*   Updated: 2021/04/20 16:34:26 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

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
	if (mode == 2)
	{
		v_tmp->value = ft_strndup(argv + i, j);
		if (v_tmp->value == NULL)
		{
			free(v_tmp);
			free(v_tmp->name);
			return (NULL);
		}
		v_tmp->on = 1;
	}
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

int		ft_check_export_name(char *str)
{
	int i;

	i = -1;
	if (ft_isalpha(str[0]) || str[0] == '_')
		i++;
	else
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (i == 0 && (ft_isalpha(str[i]) || str[i] == '_'))
			i++;
		else if (i > 0 && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		else
			return (0);
	}
	return (1);
}

int		ft_export_replace_value(t_list *exist, char *str)
{
	t_var	*v_tmp;
	char	*new;
	int		i;

	i = 0;
	printf("export node already exist \n");
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (1);
	i++; // passe le premier '=';
	new = ft_strdup(str + i);
	if (new == NULL)
		return (-1);
	v_tmp = (t_var *)exist->content;
	free(v_tmp->value);
	v_tmp->value = new;
	return (1);
}

int		ft_export_print(t_list **env, int fd_out)
{
	t_list *copy;

	copy = NULL;
	if (ft_lst_env_copy(&copy, env) == -1)
			return (-1); // Err malloc
	ft_lst_env_sort(&copy, ft_strcmp);
	ft_print_exportlst_fd(copy, fd_out);
	ft_lstclear_envlst(&copy);
	return (0);
}


int		ft_export(t_list **env, t_simple_cmd *cmd, int fd_out, t_list **error)
{
	t_list	*exist;
	char	*key;
	int		ret;
	int		res;
	char 	**argv;

	argv = cmd->av; //A REVOIR
	argv++;
	res = 0;
	if (*argv == NULL)
		return (ft_export_print(env, fd_out));
	while (*argv)
	{
		ret = 0;
		if (ft_check_export_name(*argv) == 0)
		{
			if (ft_add_error_list(error,"bash: unset: « ", *argv, " »: not a valid identifier\n") == -1)
				return (-1);
			res = 1;
		}
		else if (cmd->pipe_mod == 0)
		{
			if ((key = ft_getenv_name(*argv)) == NULL)
				return (-1);//err malloc
			if ((exist = ft_lstfind_export(env, key, ft_strcmp)))
				ret = ft_export_replace_value(exist, *argv);
			else
				ret = ft_lst_env_addback(env, *argv);
			free(key);
			if (ret == -1)
				return (-1); //err malloc
		}
		argv++;
	}
	return (res);
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