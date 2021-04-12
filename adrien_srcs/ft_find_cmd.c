/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 21:40:11 by calao             #+#    #+#             */
/*   Updated: 2021/04/12 22:52:50 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../ft.h"

int		ft_find_cmd_path(char *exec)
{
	char	**tab_path;
	char	*env_path_val;
	char	*job_path;
	char	*tmp;
	struct	stat	buff;

	//env_path_val = (char *)((ft_lstfind(env_lst, "PATH", ft_strcmp))->content);
	env_path_val = getenv("PATH");
	printf("PATH = %s\n\n", env_path_val);
	tab_path = ft_split_charset(env_path_val, ":");
	if (tab_path == NULL)
		return (-1); //command could not be found;
	
	while (*tab_path)
	{
		printf("tab_path = [%s]\n", *tab_path);
		job_path = ft_strjoin(*tab_path, "/");
		tmp = job_path;
		job_path = ft_strjoin(job_path, exec);
		free(tmp);
		printf("job_path checking ... = [%s]\n", job_path);
		if (job_path == NULL)
			return (-1);
		if (stat(job_path, &buff))
		{
			printf("stat : %s", job_path);
			if (S_ISREG(buff.st_mode)) //&& (buff.st_mode & S_IXUSR))
			{
				//free_double_tab(tab_path);
				//return (job_path);
				printf(" -- > Regular file ok");
			}
			printf("\n");
		}
		printf("\n");
		free(job_path);
		tab_path++;
	}
	return (-1); //no file corresponding to criteria was found
}
