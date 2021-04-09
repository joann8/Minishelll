/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_historylst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 15:28:51 by calao             #+#    #+#             */
/*   Updated: 2021/04/09 16:05:16 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		ft_make_loglst(t_list **log, int fd);
void	ft_print_str_lst(t_list *head);

int	ft_main_history(void)
{
	t_list *log_lst;
	int		log_size;
	int		fd_log;

	fd_log = open("minishell.log", O_RDWR | O_CREAT | O_APPEND, 0666);
	if (fd_log < 0)
		return (-1);
	log_lst = NULL;
	ft_make_loglst(&log_lst, fd_log);
	log_size = ft_lstsize(log_lst);
	printf("lst_size = %d\n", log_size);
	ft_print_str_lst(log_lst);
	close(fd_log);
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
		log = ft_strdup(line);
		free(line);
		if (log == NULL)
			return (-1);
		new_node = ft_lstnew(log);
		if (new_node == NULL)
			return (-1);
		ft_lstadd_back(head, new_node);
	}
	//Recoder une fois pour la derniere ligne ?
	return (0);
}

void	ft_print_str_lst(t_list *head)
{
	t_list *tmp;

	tmp = head;
	while (tmp)
	{
		printf("node : %s\n", (char*)tmp->content);
		tmp = tmp->next;
	}
}

		
			
