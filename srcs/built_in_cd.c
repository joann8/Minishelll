/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:09:20 by calao             #+#    #+#             */
/*   Updated: 2021/04/20 20:25:02 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		is_absolute_path(char *str)
{
	if (*str == '/')
		return (1);
	else
		return (0);
}


int		ft_make_dir_lst(t_list **dir, char *str)
{
	int		i;
	int		start;
	int		len;
	char	*tmp;
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
			tmp = ft_strndup(str + start, len);
			if (tmp == NULL)
				return (-1);
			new = ft_lstnew(tmp);
			if (new == NULL)
			{
				free (tmp);
				return (-1);
			}
			ft_lstadd_back(dir, new);
			start = i + len;
		}
		i++;
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

//cur_path = cwd //operand = r_path
char	*get_newpath(char *operand)
{
	t_list	*dir_lst;
	char	*cur_path;
	char	*new_path;

	dir_lst = NULL;
	cur_path = getcwd(NULL, 0);
	if (cur_path == NULL)
		return (NULL); //err malloc
	printf("cur_path = %s\n", cur_path);
	printf("operand = %s\n", operand);
	if (ft_make_dir_lst(&dir_lst, cur_path) == -1)
	{
		free(cur_path);
		return (NULL); //err malloc
	}
	free(cur_path);
	ft_print_str_lst(dir_lst);
	ft_edit_dir_lst(&dir_lst, operand);
	ft_print_str_lst(dir_lst);
	new_path = ft_get_absolute_path(dir_lst);
	return (new_path);
}

int		chdir_to_home_var(t_list **env, t_list **error)
{
	t_list *home_node;
	t_var	*v_tmp;

	home_node = ft_lstfind_env(env, "HOME", ft_strcmp);
	if (home_node == NULL)
	{
		add_err_lst(error, "Bash: cd: $HOME is not set\n", NULL, NULL, error);
		return (1);
	}
	v_tmp = (t_var *)home_node->content;
	if (chdir(v_tmp->value) == -1)
	{

		printf("Bash(adrien): cd: errno = %s\n", strerror(errno));
		return (1);
	}
	if (ft_update_pwd(v_tmp->value, env) == -1)
		return (-1); // err malloc
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
		
int		ft_cd(t_simple_cmd *cmd, t_list **env, t_list **error)
{
	char	*new_path;
	char	*op;

	if (cmd->ac > 2)
	{
		if (add_err_lst(error, "bash: cd: too many arguments", NULL, NULL) < 0)
			return (-1);
		return (1);
	}
	op = *(cmd->av + 1);
	if (op == NULL || ft_strcmp(op, "") == 0)
		return (chdir_to_home_var(env));
	// to change if send after v2
	new_path = (is_absolute_path(op)) ? ft_strdup(op) : get_newpath(op);
		if (new_path == NULL)
		return (-1); // Err malloc;
	if (chdir(new_path) == -1)
	{
		if (add_err_lst(error, "bash(adrien): cd: ", 
					new_path, strerror(errno), error) < 0)
			return(ft_free(new_path, -1);
		return (ft_free(new_path, 1));
	}
	if (ft_update_pwd(new_path, env) == -1)
		return (ft_free(new_path, -1);
	free(new_path);
	return (0);
}
/*
if (is_absolute_path(operand))
		new_path = ft_strdup(operand);
	else
		new_path = get_newpath(operand);
*/
