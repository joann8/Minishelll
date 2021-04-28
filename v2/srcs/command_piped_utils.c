/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_piped_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:42:47 by jacher            #+#    #+#             */
/*   Updated: 2021/04/28 12:37:09 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void		close_fd_pipe(int ***fd_pipe, int size)
{
	int j;

	j = 0;
	while (j < size + 1)
	{
		close((*fd_pipe)[j][0]);
		close((*fd_pipe)[j][1]);
		j++;
	}
}

void		clear_fd_pipe(int ***fd_pipe, int index)
{
	int i;

	i = 0;
	while (i < index)
	{
		free((*fd_pipe)[i]);
		i++;
	}
	free(*fd_pipe);
}

int			prepare_fd_pipe(int ***fd_pipe, int size)
{
	int	i;

	*fd_pipe = malloc(sizeof(int*) * (size + 1));
	if (*fd_pipe == NULL)
		return (p_error(0, "malloc error\n", -1));
	i = 0;
	while (i <= size)
	{
		(*fd_pipe)[i] = malloc(sizeof(int) * 2);
		if ((*fd_pipe)[i] == NULL)
		{
			clear_fd_pipe(fd_pipe, i);
			return (p_error(0, "malloc error\n", -1));
		}
		if (pipe((*fd_pipe)[i]) == -1)
		{
			clear_fd_pipe(fd_pipe, i + 1);
			return (print_err(strerror(errno), "\n", NULL, -1));
		}
		i++;
	}
	return (0);
}

int			set_up_child_pipes(t_simple_cmd *tmp_c, int size,
				int ***fd_pipe, int i)
{
	if (i != 0)
	{
		if (tmp_c->p.fd_in_to_use == STDIN_FILENO)
			tmp_c->p.fd_in_to_use = (*fd_pipe)[i - 1][0];
	}
	if (i + 1 != size)
	{
		if (tmp_c->p.fd_out_to_use == STDOUT_FILENO)
			tmp_c->p.fd_out_to_use = (*fd_pipe)[i][1];
	}
	return (0);
}
