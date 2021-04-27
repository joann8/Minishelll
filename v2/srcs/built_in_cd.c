/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:09:20 by calao             #+#    #+#             */
/*   Updated: 2021/04/27 13:48:05 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

// A supprimer ?
int		fake_cd(char *new_path, t_list **error, int mode)
{
	DIR	*fd_dir;

	fd_dir = opendir(new_path);
	if (mode == 1)
		free(new_path);
	if (fd_dir == NULL)
	{
		if (add_err_lst(error, "bash: cd: ", strerror(errno), "\n") == -1)
			return (-1);
		return (1);
	}
	closedir(fd_dir);
	return (0);
}

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
	char	*str;
	t_list	*new;

	tmp = ft_split(r_path, '/');
	while (*tmp)
	{
		if (ft_strcmp(*tmp, "..") == 0)
			ft_lstdel_last(dir);
		else if (ft_strcmp(*tmp, ".") != 0)
		{
			str = ft_strjoin("/", *tmp);
			if (str == NULL)
				return (-1);
			new = ft_lstnew(str);
			if (new == NULL)
			{
				free(str);
				return (-1);
			}
			ft_lstadd_back(dir, new);
		}
		tmp++;
	}
	return (0);
}

int		chdir_to_home_var(t_simple_cmd *cmd, t_list **env, t_list **error)
{
	t_list *home_node;
	t_var	*v_tmp;

	home_node = ft_lstfind_env(env, "HOME", ft_strcmp);
	if (home_node == NULL)
		return (ft_cd_error(error, "bash: cd: $HOME is not set\n", NULL, 1));
	v_tmp = (t_var *)home_node->content;
	if (cmd->pipe_mod == 0)
	{
		if (chdir(v_tmp->value) == -1)
		{
			if (add_err_lst(error, "bash: cd: ", v_tmp->value, ": ") == -1
					|| add_err_lst(error, strerror(errno), "\n", NULL) == -1)
				return (-1);
			return (1);
		}
		if (ft_update_pwd(v_tmp->value, env) == -1)
			return (-1); // err malloc
		return (0);
	}
	else
		return (fake_cd(v_tmp->value, error, 0)); 
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

int		ft_cd(t_simple_cmd *cmd, t_list **env, t_list **error)
{
	char	*new_path;
	char	*op;

	if (cmd->ac > 2)
		return(ft_cd_error(error, "bash: cd: ", "too many arguments\n", 1));
	op = *(cmd->av + 1);
	if (op == NULL || ft_strcmp(op, "") == 0 || ft_strcmp(op, "~") == 0)
		return (chdir_to_home_var(cmd,env, error));
	new_path = (is_absolute_path(op)) ? ft_strdup(op) : get_newpath(op);
	if (new_path == NULL)
		return (-1); // Err malloc;
	if (cmd->pipe_mod == 0)
	{
		if (chdir(new_path) == -1)
		{
			if (add_err_lst(error, "bash: cd: ", new_path, NULL) == -1 ||
					add_err_lst(error, ": ", strerror(errno), "\n") == -1)
				return(ft_free(new_path, -1));
			return (ft_free(new_path, 1));
		}
		if (ft_update_pwd(new_path, env) == -1)
			return (ft_free(new_path, -1));
		return (ft_free(new_path, 0));
	}
	else
		return (fake_cd(new_path, error, 1));
}

/*
	if (is_absolute_path(op))
		new_path = ft_strdup(op);
	else
		new_path = get_newpath(op);
		*/
