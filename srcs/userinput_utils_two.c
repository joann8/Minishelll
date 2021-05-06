/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   userinput_utils_two.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:09:21 by calao             #+#    #+#             */
/*   Updated: 2021/05/04 15:56:14 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		ft_update_log(char **screen, t_list **log, int fd_log)
{
	char			*last_log;
	unsigned int	log_size;
	unsigned int	s_len;
	t_list			*new;

	s_len = ft_strlen(*screen);
	log_size = ft_lstsize(*log);
	if (log_size > 0)
		last_log = (char *)((ft_lstat(*log, log_size - 1))->content);
	else
		last_log = "";
	if (ft_strcmp(*screen, last_log)
			&& !ft_is_only_space(*screen))
	{
		write(fd_log, *screen, s_len);
		write(fd_log, "\n", 1);
		new = ft_lstnew(ft_strdup(*screen));
		if (new == NULL)
			return (-1);
		ft_lstadd_back(log, new);
	}
	write(1, "\n", 1);
	return (0);
}

int		ft_make_loglst(t_list **head, int fd)
{
	t_list	*new_node;
	char	*line;
	char	*log;

	new_node = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		new_node = ft_lstnew(NULL);
		if (new_node == NULL)
			return (-1);
		ft_lstadd_back(head, new_node);
		log = ft_strdup(line);
		free(line);
		if (log == NULL)
			return (-1);
		new_node->content = log;
	}
	free(line);
	return (0);
}
