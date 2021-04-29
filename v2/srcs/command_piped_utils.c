/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_piped_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:42:47 by jacher            #+#    #+#             */
/*   Updated: 2021/04/29 18:50:44 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void		close_fd_pipe(int ***fd_pipe, int size, int mod)
{
	int j;

	j = 0;
	if (mod == 0)
	{
		while (j < size + 1)
		{
			close((*fd_pipe)[j][0]);
			close((*fd_pipe)[j][1]);
			j++;
		}
	}
	if (mod == 1)
	{
		while ((*fd_pipe)[j])
		{
			close((*fd_pipe)[j][0]);
			close((*fd_pipe)[j][1]);
			j++;
		}
	}
}

void		clear_fd_pipe(int ***fd_pipe, int index, int mod)
{
	int i;

	i = 0;
	if (mod == 0)
	{
		while (i < index)
		{
			free((*fd_pipe)[i]);
			i++;
		}
		free(*fd_pipe);
	}
	if (mod == 1)
	{
		while ((*fd_pipe)[i])
		{
			free((*fd_pipe)[i]);
			i++;
		}
		free(*fd_pipe);
	}
}

int			prepare_fd_pipe(int ***fd_pipe, int size)
{
	int	i;

	*fd_pipe = malloc(sizeof(int*) * (size + 2));
	if (*fd_pipe == NULL)
		return (p_error(0, "malloc error\n", -1));
	i = 0;
	while (i <= size)
	{
		(*fd_pipe)[i] = malloc(sizeof(int) * 2);
		if ((*fd_pipe)[i] == NULL)
		{
			clear_fd_pipe(fd_pipe, i, 0);
			return (p_error(0, "malloc error\n", -1));
		}
		if (pipe((*fd_pipe)[i]) == -1)
		{
			clear_fd_pipe(fd_pipe, i + 1, 0);
			return (print_err(strerror(errno), "\n", NULL, -1));
		}
		i++;
	}
	(*fd_pipe)[i] = NULL;
	return (0);
}

int			set_up_child_pipes(t_simple_cmd *tmp_c, int size,
				int ***fd_pipe, int i)
{
	if (tmp_c->job == NULL || tmp_c->on == 0)
	{
		close_fd_pipe(fd_pipe, 0, 1);
		g.exit_status = 0;
		return (-1);
	}
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

int		prepare_execution(int ***fd_pipe, int **pid_list, int size)
{
	*pid_list = malloc(sizeof(int) * size);
	if (pid_list == NULL)
		return (-1);
	if (prepare_fd_pipe(fd_pipe, size) == -1)
	{
		free(pid_list);
		return (-1);
	}
	return (0);
}
