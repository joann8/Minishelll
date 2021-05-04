/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:09:20 by calao             #+#    #+#             */
/*   Updated: 2021/05/03 22:34:47 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		ft_make_dir_lst(t_list **dir, char *str)
{
	int		i;
	int		start;
	int		len;
	t_list	*new;

	start = 0;
	i = 0;
	while (str[i])
	{
		len = 0;
		if (str[i] == '/')
		{
			while (str[i + len] && str[i + len + 1] != '/')
				len++;
			if (str[i + len])
				len++;
			new = ft_lstnew(NULL);
			if (new == NULL || !(new->content = ft_strndup(str + start, len)))
				return (-1);
			ft_lstadd_back(dir, new);
			start = i + len;
		}
		i++;
	}
	return (0);
}

int		ft_edit_dir_lst(t_list **dir, char *r_path)
{
	char	**tmp;
	int		i;
	t_list	*new;

	tmp = ft_split(r_path, '/');
	if (tmp == NULL)
		return (-1);
	i = -1;
	while (tmp[++i])
	{
		if (ft_strcmp(tmp[i], "..") == 0)
			ft_lstdel_last(dir);
		else if (ft_strcmp(tmp[i], ".") != 0)
		{
			new = ft_lstnew(ft_strjoin("/", tmp[i]));
			if (new == NULL || new->content == NULL)
			{
				free_double_tab(tmp);
				return (-1);
			}
			ft_lstadd_back(dir, new);
		}
	}
	free_double_tab(tmp);
	return (0);
}

int		chdir_to_home_var(t_list **env)
{
	t_list	*home_node;
	t_var	*v_tmp;

	home_node = ft_lstfind_env(env, "HOME", ft_strcmp);
	if (home_node == NULL)
		return (print_err("msh: cd: $HOME is not set\n", "", "", 1));
	v_tmp = (t_var *)home_node->content;
	if (ft_strcmp(v_tmp->value, "") == 0)
		return (print_err("msh: cd: $HOME is not set\n", "", "", 1));
	if (chdir(v_tmp->value) == -1)
	{
		print_err("msh: cd: ", v_tmp->value, ": ", 0);
		return (print_err(strerror(errno), "\n", NULL, 1));
	}
	if (ft_update_pwd(v_tmp->value, env) == -1)
		return (-1);
	return (0);
}

int		ft_update_pwd(char *new_path, t_list **env)
{
	t_list	*pwd;
	t_list	*o_pwd;
	t_var	*o_tmp;
	t_var	*p_tmp;

	o_pwd = ft_lstfind_env(env, "OLDPWD", ft_strcmp);
	pwd = ft_lstfind_env(env, "PWD", ft_strcmp);
	if (o_pwd && pwd)
	{
		o_tmp = (t_var *)o_pwd->content;
		p_tmp = (t_var *)pwd->content;
		free(o_tmp->value);
		o_tmp->value = ft_strdup(p_tmp->value);
		if (o_tmp->value == NULL)
			return (-1);
	}
	if (pwd)
	{
		p_tmp = (t_var *)pwd->content;
		free(p_tmp->value);
		p_tmp->value = ft_strdup(new_path);
		if (p_tmp->value == NULL)
			return (-1);
	}
	return (0);
}

int		ft_cd(t_simple_cmd *cmd, t_list **env)
{
	char	*new_path;
	char	*op;

	if (cmd->ac > 2)
		return (print_err("msh: cd: ", "too many arguments\n", NULL, 1));
	op = *(cmd->av + 1);
	if (op == NULL || ft_strcmp(op, "") == 0 || ft_strcmp(op, "~") == 0)
		return (chdir_to_home_var(env));
	if (is_absolute_path(op))
		new_path = ft_strdup(op);
	else if (op[0] == '.')
		new_path = get_newpath(op);
	else
		new_path = ft_cd_path(op, env);
	if (new_path == NULL)
		return (-1);
	if (chdir(new_path) == -1)
	{
		print_err("msh: cd: ", op, "", 0);
		print_err(": ", strerror(errno), "\n", 1);
		return (ft_free(new_path, 1));
	}
	if (ft_update_pwd(new_path, env) == -1)
		return (ft_free(new_path, -1));
	return (ft_free(new_path, 0));
}
