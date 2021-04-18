/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:09:20 by calao             #+#    #+#             */
/*   Updated: 2021/04/18 17:11:05 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		ft_path_is_relative(char *str)
{
	if (*str == '/')
		return (0);
	else
		return (1);
}


char	*ft_my_getcwd(void)
{
	char	*cwd;
	char	*tmp;
	size_t	size;
	int		i;

	size = 10;
	cwd = NULL;
	i = 0;
	while (cwd == NULL)
	{
		cwd = getcwd(cwd, size);
		if (cwd == NULL)
		{
			if (errno == ERANGE)
				size += 20;
			else
				return (NULL);
		}
		i++;
	}
	tmp = cwd;
	cwd = ft_strjoin(cwd, "/");
	free(tmp);
	return (cwd);
}

int		ft_make_dir_lst(t_list **dir, char *str)
{
	int		start;
	int		end;
	char	*tmp;
	
	start = 0;
	end = 0;
	while (str[end])
	{
		if (end != 0 && (str[end] == '/' || str[end + 1] == '\0'))
		{
			tmp = ft_strndup(str + start, end - start);
			if (tmp == NULL)
				return (-1);
			ft_lstadd_back(dir, ft_lstnew(tmp));
			//printf("tmp = %s\n", tmp);
			start = end;
		}
		end++;
	}
	return (0);
}

void	ft_lstdel_last(t_list **head)
{
	int		size;
	t_list	*last;
	t_list	*previous_to_last;

	size = ft_lstsize(*head);
	if (size == 0 || *head == NULL)
	{
		if (size == 0)
			printf("size == 0\n");
		if (*head == NULL)	
			printf("*head == NULL\n");
		return ; // Rien a supprimer la liste est vide
	}
	else if (size == 1)
	{
		last = ft_lstat(*head, 0);
		ft_lstdelone(last, free);
		*head = NULL;
	}
	else
	{
		last = ft_lstat(*head, size - 1);
		previous_to_last = ft_lstat(*head, size - 2);
		previous_to_last->next = NULL;
		ft_lstdelone(last, free);
	}
}

int		ft_edit_dir_lst(t_list **dir, char *r_path)
{
	char **tmp;
	char *str;


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
			ft_lstadd_back(dir, ft_lstnew(str));
		}
		tmp++;
	}
	return (0);

}

char	*ft_get_absolute_path(t_list *dir)
{
	char *final_path;
	char *tmp;

	final_path = NULL;
	if (dir == NULL)
		return (ft_strdup("/"));
	while (dir)
	{
		tmp = final_path;
		final_path = ft_strjoin(final_path, (char *)dir->content);
		free(tmp);
		if (final_path == NULL)
			return (NULL);
		dir = dir->next;
	}
	return (final_path);
}

char	*ft_relative_to_absolute(char *r_path)
{
	char	*cwd;
	t_list	*dir_lst;

	dir_lst = NULL;

	if (ft_path_is_relative(r_path))
	{
		printf("**RELATIVE PATH:\n");
		cwd = ft_my_getcwd();
	}
	else
	{
		printf("**ABSOLUTE PATH:\n");
		cwd = ft_strdup("/");
	}
	if (cwd == NULL)
		return (NULL);
	printf("cwd = %s\n", cwd);
	printf("r_path = %s\n", r_path);
	if (ft_make_dir_lst(&dir_lst, cwd) == -1)
		return (NULL);
	free(cwd);
	ft_print_str_lst(dir_lst);
	ft_edit_dir_lst(&dir_lst, r_path);
	ft_print_str_lst(dir_lst);
	cwd = ft_get_absolute_path(dir_lst);
	printf("abs_path = %s\n", cwd);
	if (chdir(cwd) == 0)
	{
		printf("chdir(0) = sucess\n");
		//printf("new cwd = %s\n", cwd);
		return (cwd);
	}
	printf("chdir(%d): errno = %s\n", chdir(cwd), strerror(errno));
	return (0);
}

char	*get_curpath(char *operand)
{
	if (ft_path_is_relative(operand))
			return (getcwd(NULL, 0));
	else
		return (ft_strdup("/"));
}

int		ft_tablen(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int		move_to_home_var(t_list **env)
{
	t_list *home_node;
	t_var	*v_tmp;

	home_node = ft_lstfind_env(env, "HOME", ft_strcmp);
	if (home_node == NULL)
	{
		printf("Bash(adrien): cd: HOME is not set\n");
		return (1);
	}
	v_tmp = (t_var *)home_node->content;
	if (chdir(v_tmp->value) == -1)
	{
		printf("Bash(adrien): cd: errno = %s\n", strerror(errno));
		return (1);
	}
	//ft_update_oldpwd(env);
	//ft_update_pwd(env);
	return (0);
}
int		ft_cd(char **argv, t_list **env)
{
	//char	*cur_path;
	//char	*new_path;
	char	*operand;

	if (ft_tablen(argv) > 2)
	{
		printf("bash: cd: too many arguments\n");
		return (1);
	}
	operand = *(argv + 1);
	// Ici add gestion (cd | cd ~) et (cd -) ? 
	if (operand == NULL || ft_strcmp(operand, "") == 0)
		return (move_to_home_var(env));
	/*
	cur_path = get_curpath(operand);
	if (cur_path == NULL)
		return (-1);
	new_path = get_newpath(curpath, operand);
	free(cur_path);
	if (new_path == NULL)
		return (-1); // Err malloc;
	if (!ft_is_directory(new_path))
	{
		printf("Bash(adrien): cd: [%s] is not a directory\n", new_path);
		free(cur_path);
		free(new_path);
		return (1);
	}
	ft_change_current_directory();
		//Change de directory ver new_path
		//Actualise OLDPWD:
		//	if (OLDPWD) && (PWD)
		//		free(OLDPWD->value);
		//		OLDPWD->value = ft_strdup(PWD->value);
		//Actualise PWD:
		//	if (PWD)
		//		free(PWD->value)
		//		PWD->value = ft_strdup(new_path);
		return (0);
		*/
	return (0);
}
