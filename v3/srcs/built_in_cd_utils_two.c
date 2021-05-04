/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd_utils_two.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:09:20 by calao             #+#    #+#             */
/*   Updated: 2021/05/03 22:36:13 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

char	*ft_dir_path(int len, char *path_to_test, char *exec)
{
	char *tmp;
	char *str;

	if (path_to_test[len - 1] != '/')
	{
		str = ft_strjoin(path_to_test, "/");
		if (str == NULL)
			return (NULL);
		tmp = str;
		str = ft_strjoin(str, exec);
		free(tmp);
		if (str == NULL)
			return (NULL);
	}
	else
	{
		str = ft_strjoin(path_to_test, exec);
		if (str == NULL)
			return (NULL);
	}
	return (str);
}

int		ft_cd_path_two(char *path_to_test, char *exec, char **job)
{
	char	*dir_path;
	int		len;
	DIR		*d_stream;

	len = ft_strlen(path_to_test);
	dir_path = ft_dir_path(len, path_to_test, exec);
	if (dir_path == NULL)
		return (-1);
	d_stream = opendir(dir_path);
	if (d_stream != NULL)
	{
		*job = dir_path;
		closedir(d_stream);
		return (0);
	}
	free(dir_path);
	return (1);
}

char	*ft_cd_path(char *operand, t_list **env)
{
	t_list	*cd_path;
	char	**path_tab;
	char	*str;
	int		ret;
	int		i;

	cd_path = ft_lstfind_env(env, "CDPATH", ft_strcmp);
	if (cd_path == NULL || !ft_strcmp(((t_var *)cd_path->content)->value, "")
		|| ((t_var *)cd_path->content)->on == 0)
		return (get_newpath(operand));
	path_tab = ft_split(((t_var *)cd_path->content)->value, ':');
	if (path_tab == NULL)
		return (NULL);
	i = -1;
	while (path_tab[++i])
	{
		if ((ret = ft_cd_path_two(path_tab[i], operand, &str)) != 1)
			break ;
	}
	free_double_tab(path_tab);
	if (ret == -1)
		return (NULL);
	if (ret == 1)
		return (get_newpath(operand));
	return (str);
}
