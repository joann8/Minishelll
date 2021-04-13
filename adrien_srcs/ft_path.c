/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:09:20 by calao             #+#    #+#             */
/*   Updated: 2021/04/13 20:41:54 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

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
			printf("tour %d\n", i);
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

int		ft_relative_to_absolute(char *r_path)
{
	char	*cwd;
	t_list	*dir_lst;
	(void)r_path;

	dir_lst = NULL;
	cwd = ft_my_getcwd();
	if (cwd == NULL)
		return (-1);
	printf("cwd = %s\n", cwd);
	printf("r_path = %s\n", r_path);
	if (ft_make_dir_lst(&dir_lst, cwd) == -1)
		return (-1);
	free(cwd);
	ft_print_str_lst(dir_lst);
	ft_edit_dir_lst(&dir_lst, r_path);
	ft_print_str_lst(dir_lst);
	cwd = ft_get_absolute_path(dir_lst);
	printf("abs_path = %s\n", cwd);
	return (0);
}

