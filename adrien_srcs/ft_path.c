/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:09:20 by calao             #+#    #+#             */
/*   Updated: 2021/04/13 19:21:41 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

char	*ft_my_getcwd(void)
{
	char	*cwd;
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
	return (cwd);
}

int		ft_make_dirlst(t_list **head, char *str)
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
			ft_lstadd_back(head, ft_lstnew(tmp));
			//printf("tmp = %s\n", tmp);
			start = end;
		}
		end++;
	}
	return (0);
}


int		ft_relative_to_absolute(char *r_path)
{
	char	*cwd;
	t_list	*dir_lst;

	dir_lst = NULL;
	cwd = ft_my_getcwd();
	if (cwd == NULL)
		return (-1);
	r_path = cwd;
	printf("cwd = %s\n", r_path);
	if (ft_make_dirlst(&dir_lst, cwd) == -1)
		return (-1);
	//free(cwd);
	ft_print_str_lst(dir_lst);
	return (0);
}

