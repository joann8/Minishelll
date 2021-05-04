/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_piped_child.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:42:47 by jacher            #+#    #+#             */
/*   Updated: 2021/05/03 23:15:59 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		execute_child_process_bis(t_simple_cmd *tmp_c, char **our_envp,
			int ***fd_pipe, char *job)
{
	if (dup2(tmp_c->p.fd_out_to_use, STDOUT_FILENO) == -1
		|| dup2(tmp_c->p.fd_in_to_use, STDIN_FILENO) == -1)
	{
		close_fd_pipe(fd_pipe, 0, 1);
		return (-1);
	}
	close_fd_pipe(fd_pipe, 0, 1);
	if ((g_msh.exit_status = execve(job, tmp_c->av, our_envp)) == -1)
		print_err(strerror(errno), NULL, NULL, 0);
	free(job);
	return (-1);
}

int		execute_child_process(t_simple_cmd *tmp_c, t_list **env,
			char **our_envp, int ***fd_pipe)
{
	int		built_in_found;
	int		res;
	char	*job;

	if ((built_in_found = find_built_in(tmp_c, env)) == 1)
	{
		res = ft_search_job_path(&job, tmp_c->av[0], env);
		if (res == -1)
		{
			close_fd_pipe(fd_pipe, 0, 1);
			return (-1);
		}
		else if (res == 0)
		{
			res = execute_cmd_path_not_found(tmp_c, 0);
			close_fd_pipe(fd_pipe, 0, 1);
			return (res);
		}
		return (execute_child_process_bis(tmp_c, our_envp, fd_pipe, job));
	}
	close_fd_pipe(fd_pipe, 0, 1);
	return (g_msh.exit_status);
}
