/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_piped.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:42:47 by jacher            #+#    #+#             */
/*   Updated: 2021/04/27 19:40:58 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		find_cmd_piped(t_simple_cmd *tmp_c, t_list **env, char **our_envp, int size, int ***fd_pipe)
{
	int		built_in_found;
	int		res;
	char	*job;

	if ((built_in_found = find_built_in(tmp_c, env)) == 1)
	//if different 0, execute build in in built in
	{
		res = ft_search_job_path(&job, tmp_c->job, env);
		if (res == -1)
			return (-1);
		else if (res == 0)
			return (execute_cmd_path_not_found(tmp_c));
			//close(&fd_pipe, size);
		else
		{
			if (dup2(tmp_c->p.fd_out_to_use, STDOUT_FILENO) == -1
				|| dup2(tmp_c->p.fd_in_to_use, STDIN_FILENO) == -1)
				return (-1);
			close_fd_pipe(fd_pipe, size);
			if (execve(job, tmp_c->av, our_envp) == -1)
				print_err(strerror(errno), NULL, NULL, 0);
			free(job);
			exit(255);
		}
	}
	close_fd_pipe(fd_pipe, size);
	return (built_in_found);//0 built in, -1 erreur built in, 227 exit*/
}

int		execute_main_process(int ***fd_pipe, int size)
{
	int		i;
	int		wstatus;

	close_fd_pipe(fd_pipe, size);
	clear_fd_pipe(fd_pipe, size);
	i = 0;
	while (i < size)
	{
		if (wait(&wstatus) == -1)
		{
			g.exit_status = 126;//return the status code
			return (-1);
		}
		i++;
	}
	if (g.exit_status != 130 && g.exit_status != 131)
		g.exit_status = WEXITSTATUS(wstatus);//return the status code
	return (0);
}

int		execute_cmd_piped(t_simple_cmd *begin, char **our_envp, t_list **env)
{
	t_simple_cmd	*tmp_c;
	int				pid_list[begin->p.size];
	int				i;
	int				**fd_pipe;

	i = 0;
	tmp_c = begin;
	fd_pipe = NULL;
	if (prepare_fd_pipe(&fd_pipe, begin->p.size) == -1)
		return (-1);
	while (i < begin->p.size && tmp_c)
	{
		if ((pid_list[i] = fork()) == -1)
			return (print_err(strerror(errno), "\n", NULL, -1));
		if (pid_list[i] == 0)
		{
			if (set_up_child_pipes(tmp_c, begin->p.size, &fd_pipe, i) == -1)
			{	
				g.exit_status = 1;
				exit(1);
			}
			if (tmp_c->on == 1)
				exit(find_cmd_piped(tmp_c, env, our_envp, begin->p.size, &fd_pipe));
			else
			{
				close_fd_pipe(&fd_pipe, begin->p.size);
				g.exit_status = 1;
				exit(1);
			}
		}
		tmp_c = tmp_c->next_pipe;
		i++;
	}
	return ((execute_main_process(&fd_pipe, begin->p.size)));
}

int		execute_piped(t_simple_cmd *begin, t_list **env)
{
	char	**our_envp;
	int		res;

	our_envp = NULL;
	if ((our_envp = ft_make_ourenvp(env)) == NULL)
		return (p_error(0, "malloc error\n", -1));
	res = execute_cmd_piped(begin, our_envp, env);
	free_double_tab(our_envp);
	return (res);
}
