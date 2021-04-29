/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:09:20 by calao             #+#    #+#             */
/*   Updated: 2021/04/29 11:01:33 by calao            ###   ########.fr       */
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

void	ft_lstdel_last(t_list **head)
{
	int		size;
	t_list	*last;
	t_list	*previous_to_last;

	size = ft_lstsize(*head);
	if (size == 0 || *head == NULL)
		return ;
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

char	*get_newpath(char *operand)
{
	t_list	*dir_lst;
	char	*cur_path;
	char	*new_path;

	dir_lst = NULL;
	cur_path = getcwd(NULL, 0);
	if (cur_path == NULL)
	{
		print_err("msh: cd: getcwd failed\n", NULL, NULL, 0);
		return (NULL);
	}
	if (ft_make_dir_lst(&dir_lst, cur_path) == -1)
	{
		ft_lstclear(&dir_lst, free);
		free(cur_path);
		return (NULL);
	}
	free(cur_path);
	ft_edit_dir_lst(&dir_lst, operand);
	new_path = ft_get_absolute_path(dir_lst);
	ft_lstclear(&dir_lst, free);
	return (new_path);
}
