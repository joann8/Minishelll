/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 21:40:11 by calao             #+#    #+#             */
/*   Updated: 2021/04/13 12:32:32 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../ft.h"


int		ft_is_file_executable(char *filename, char *filepath)
{
	char *tmp;
	struct stat sb;


	tmp = ft_strjoin(filepath, filename);
	if (tmp == NULL)
		return (-1);

	if (stat(tmp, &sb) == 0)
	{
		if (S_ISREG(sb.st_mode))
		{
			if (sb.st_mode & S_IXUSR)
			{
				free(tmp);
				return (1);
			}
		}
	}
	free(tmp);
	return (0);
}

int		ft_search_dir(char *exec, char *dir_path)
{
	struct dirent	*s_dir;
	DIR				*d_stream;

	d_stream = opendir(dir_path);
	if (!d_stream)
		return (0); // error d'ouverture du dossier
	while (1)
	{
		s_dir = readdir(d_stream);
		if (!s_dir)
		{
			if (closedir(d_stream))
				return (0);
			return (0);
		}
		if (ft_strcmp(exec, s_dir->d_name) == 0)
		{
			if (s_dir->d_type == DT_REG)
			{
				if (ft_is_file_executable(s_dir->d_name, dir_path))
				{
					printf("\tcommand [%s] found !\n\n", exec);
					if (closedir(d_stream))
						return (0);
					return (1);
				}
			}
		}
	}
}

char	*ft_find_cmd_path(char *exec)
{
	char	**dir_tab;
	char	*env_path_val;
	char	*dir_path;
	char	*tmp;
//	struct	stat	buff;

	//env_path_val = (char *)((ft_lstfind(env_lst, "PATH", ft_strcmp))->content);
	env_path_val = getenv("PATH");
//	printf("PATH = %s\n\n", env_path_val);
	dir_tab = ft_split_charset(env_path_val, ":");
	if (dir_tab == NULL)
		return (NULL); //command could not be found;
	while (*dir_tab)
	{
		dir_path = ft_strjoin(*dir_tab, "/");
		if (dir_path == NULL)
			return (NULL);
	//	dir_path = ft_strdup(*dir_tab);
		printf("searching for:[%s] in dir:[%s]:\n", exec, dir_path);
		if (ft_search_dir(exec, dir_path))
		{
			tmp = dir_path;
			dir_path = ft_strjoin(dir_path, exec);
			free(tmp);
			if (dir_path == NULL)
				return (NULL);
			return (dir_path);
		}
		printf("\n");
		free(dir_path);
		dir_tab++;
	}
	return (NULL); //no file corresponding to criteria was found
}

	/*if (stat(job_path, &buff))
		{
			printf("stat : %s", job_path);
			if (S_ISREG(buff.st_mode)) //&& (buff.st_mode & S_IXUSR))
			{
				//free_double_tab(tab_path);
				return (job_path);
			}
			printf("\n");
			*/
