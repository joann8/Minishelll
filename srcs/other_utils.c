/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 10:01:01 by calao             #+#    #+#             */
/*   Updated: 2021/04/20 17:13:21 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		ft_is_file_executable(char *filepath)
{
	struct stat sb;

	if (stat(filepath, &sb) == 0)
	{
		if (S_ISREG(sb.st_mode))
		{
			if (sb.st_mode & S_IXUSR)
				return (1);
		}
	}
	return (0);
}

int		ft_lst_on_env_size(t_list **env)
{
	t_list	*node;
	t_var	*var;
	int		i;

	i = 0;
	node = *env;
	while (node)
	{
		var = (t_var *)(node->content);
		if (var->on)
			i++;
		node = node->next;
	}
	return (i);
}

void	ft_swap_content(t_list *a, t_list *b)
{
	void	*tmp;

	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
}

int		ft_is_only_space(char *str)
{
	while (*str)
	{
		if (*str != ' ')
			return (0);
		str++;
	}
	return (1);
}

char	*ft_strndup(char *src, int len)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(sizeof(*dest) * (len + 1));
	if (dest == NULL)
		return (NULL);
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

