/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_exec_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 21:40:11 by calao             #+#    #+#             */
/*   Updated: 2021/05/03 23:23:11 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		ft_init_path(char **env_path, t_list **env)
{
	t_var	*var_tmp;
	t_list	*node_tmp;

	node_tmp = ft_lstfind_env(env, "PATH", ft_strcmp);
	if (node_tmp == NULL)
		return (-1);
	var_tmp = (t_var *)(node_tmp->content);
	if (var_tmp->on == 0)
		return (-1);
	*env_path = var_tmp->value;
	return (1);
}

int		ft_search_env_path_two(char *path_to_test, char *exec, char **job)
{
	char	*dir_path;
	int		ret;

	dir_path = ft_strjoin(path_to_test, "/");
	if (dir_path == NULL)
		return (-1);
	ret = ft_search_dir(exec, dir_path);
	if (ret == -1)
	{
		free(dir_path);
		return (-1);
	}
	else if (ret == 0)
	{
		*job = ft_strjoin(dir_path, exec);
		free(dir_path);
		if (*job == NULL)
			return (-1);
		return (1);
	}
	free(dir_path);
	return (0);
}

int		search_env_path_var(char **job, char *exec, t_list **env)
{
	char	**dir_tab;
	char	*env_path_val;
	int		i;
	int		ret;

	if (ft_init_path(&env_path_val, env) == -1)
		return (0);
	dir_tab = ft_split(env_path_val, ':');
	if (dir_tab == NULL)
		return (-1);
	i = 0;
	while (dir_tab[i])
	{
		ret = ft_search_env_path_two(dir_tab[i], exec, job);
		if (ret == 1 || ret == -1)
		{
			free_double_tab(dir_tab);
			return (ret);
		}
		i++;
	}
	free_double_tab(dir_tab);
	return (0);
}

int		search_relative_path(char **job, char *exec_relative_path)
{
	char *job_abs_path;

	job_abs_path = get_newpath(exec_relative_path);
	if (job_abs_path == NULL)
		return (-1);
	if (ft_is_file_executable(job_abs_path) == 1)
	{
		*job = job_abs_path;
		return (1);
	}
	free(job_abs_path);
	return (0);
}

int		ft_search_job_path(char **job_output, char *exec_input, t_list **env)
{
	if (exec_input[0] == '/')
	{
		if (ft_is_file_executable(exec_input))
		{
			*job_output = ft_strdup(exec_input);
			if (job_output == NULL)
				return (-1);
			return (1);
		}
		return (0);
	}
	else if (exec_input[0] == '.')
		return (search_relative_path(job_output, exec_input));
	else
		return (search_env_path_var(job_output, exec_input, env));
}
