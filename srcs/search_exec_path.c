/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_cmd_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 21:40:11 by calao             #+#    #+#             */
/*   Updated: 2021/04/17 14:50:58 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../ft.h"


int		ft_is_file_executable(char *filename, char *filepath)
{
	char tmp[ft_strlen(filepath) + ft_strlen(filename) + 1];
	struct stat sb;


	ft_strcpy(tmp, filepath);
	ft_strcpy(tmp + ft_strlen(filepath), filename);
	if (stat(tmp, &sb) == 0)
	{
		if (S_ISREG(sb.st_mode))
		{
			if (sb.st_mode & S_IXUSR)
				return (1);
		}
	}
	return (0);
}

int		ft_search_dir(char *exec, char *dir_path)
{
	struct dirent	*s_dir;
	DIR				*d_stream;

	d_stream = opendir(dir_path);
	if (!d_stream)
		return (0);// error d'ouverture du dossier
	while (1)
	{
		s_dir = readdir(d_stream);
		if (!s_dir)
		{
			if (closedir(d_stream))
				return (-1); // err fermeture
			return (0); // Pas trouver
		}
		if (ft_strcmp(exec, s_dir->d_name) == 0 && s_dir->d_type == DT_REG
				&& ft_is_file_executable(s_dir->d_name, dir_path))
		{
			if (closedir(d_stream))
				return (-1);
			return (1); // trouver
		}
	}
}

int	ft_init_path(char **env_path, t_list **env)
{
	t_var *var_tmp;
	t_list *node_tmp;

	node_tmp = ft_lstfind_env(env, "PATH", ft_strcmp);
	if (node_tmp == NULL)
		return (-1); // PATH n'existe pas du tout (unset)
	var_tmp = (t_var *)(node_tmp->content);
	if (var_tmp->on == 0)
		return (-1);// PATH est export mais pas SET
	*env_path = var_tmp->value;
	return (1);
}


int		ft_find_cmd_path(char **job, char *exec, t_list **env)
{

	//INT A ENVOYER POUR DIFFERENCIER -2 pbm ouverture de dossier
	//-1  malloc 1 trouve 0 pas touve
	char	**dir_tab;
	char	*env_path_val;
	char	*dir_path;
	char	*tmp;
	int		i;
	int		ret;
	
	if (ft_init_path(&env_path_val, env) == -1)
		return (0); // La variable PATH n'existe pas
	dir_tab = ft_split(env_path_val, ':');
	if (dir_tab == NULL)
		return (-1); //Err malloc 
	i = 0;
	while (dir_tab[i])
	{
		dir_path = ft_strjoin(dir_tab[i], "/");
		if (dir_path == NULL)
			return (-1); //Err malloc
		ret = ft_search_dir(exec, dir_path);
		if (ret == -1)
			return (-2);
		else if (ret == 1)
		{
			tmp = dir_path;
			dir_path = ft_strjoin(dir_path, exec);
			free(tmp);
			free_double_tab(dir_tab);
			if (dir_path == NULL)
				return (-1);
			*job = dir_path;
			return (1);
		}
		free(dir_path);
		i++;
	}
	free_double_tab(dir_tab);
	return (0); //no file corresponding to criteria was found
}
