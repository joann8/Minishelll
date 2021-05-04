/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 23:15:48 by calao             #+#    #+#             */
/*   Updated: 2021/05/03 23:16:03 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		ft_search_dir(char *exec, char *dir_path)
{
	struct dirent	*s_dir;
	DIR				*d_stream;
	char			*filepath;

	d_stream = opendir(dir_path);
	if (!d_stream)
		return (1);
	while ((s_dir = readdir(d_stream)) != NULL)
	{
		if (ft_strcmp(exec, s_dir->d_name) == 0 && s_dir->d_type == DT_REG)
		{
			filepath = ft_strjoin(dir_path, s_dir->d_name);
			if (filepath == NULL)
				return (-1);
			if (ft_is_file_executable(filepath) == 1)
			{
				free(filepath);
				closedir(d_stream);
				return (0);
			}
			free(filepath);
		}
	}
	closedir(d_stream);
	return (1);
}
