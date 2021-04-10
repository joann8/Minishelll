/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_loglst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:28:51 by calao             #+#    #+#             */
/*   Updated: 2021/04/10 10:59:54 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		ft_make_loglst(t_list **log, int fd);

int		ft_make_loglst(t_list **head, int fd)
{
	t_list	*new_node;
	char	*line;
	char	*log;

	new_node = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		log = ft_strdup(line);
		free(line);
		if (log == NULL)
			return (-1);
		new_node = ft_lstnew(log);
		if (new_node == NULL)
			return (-1);
		ft_lstadd_back(head, new_node);
	}
	free(line);
	//Recoder une fois pour la derniere ligne ?
	return (0);
}
