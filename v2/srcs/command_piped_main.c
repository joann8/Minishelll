/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_piped_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:42:47 by jacher            #+#    #+#             */
/*   Updated: 2021/05/03 23:17:33 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		kill_processes(int *pid_list)
{
	while (*pid_list > 0)
	{
		if (kill(*pid_list, SIGKILL))
		{
			free(pid_list);
			return (-1);
		}
		pid_list++;
	}
	return (0);
}

int		execute_main_process(t_simple_cmd *tmp_c, int *pid_list,
			int ***fd_pipe, int size)
{
	int		i;
	int		wstatus;

	close_fd_pipe(fd_pipe, size, 1);
	clear_fd_pipe(fd_pipe, size + 1, 1);
	i = 0;
	if (tmp_c)
		if (kill_processes(pid_list) == -1)
			return (-1);
	free(pid_list);
	while (i < size)
	{
		if (wait(&wstatus) == -1)
		{
			g_msh.exit_status = 126;
			return (-1);
		}
		i++;
	}
	g_msh.exit_status = WEXITSTATUS(wstatus);
	return (0);
}

int		execute_piped_bis(t_simple_cmd *begin, char **our_envp, t_list **env)
{
	t_simple_cmd	*tmp_c;
	int				*pid_list;
	int				**fd_pipe;
	int				i;

	i = 0;
	tmp_c = begin;
	fd_pipe = NULL;
	pid_list = NULL;
	if (prepare_execution(&fd_pipe, &pid_list, begin->p.size) == -1)
		return (-1);
	while (i < begin->p.size && tmp_c)
	{
		if ((pid_list[i] = fork()) == -1)
			exit((print_err(strerror(errno), "\n", NULL, -1)));
		if (pid_list[i] == 0)
		{
			if (set_up_child_pipes(tmp_c, begin->p.size, &fd_pipe, i) == -1)
				exit(0);
			exit(execute_child_process(tmp_c, env, our_envp, &fd_pipe));
		}
		tmp_c = tmp_c->next_pipe;
		i++;
	}
	return ((execute_main_process(tmp_c, pid_list, &fd_pipe, begin->p.size)));
}

int		execute_piped(t_simple_cmd *begin, t_list **env)
{
	char	**our_envp;
	int		res;

	our_envp = NULL;
	if ((our_envp = ft_make_ourenvp(env)) == NULL)
		return (p_error(0, "malloc error\n", -1));
	res = execute_piped_bis(begin, our_envp, env);
	free_double_tab(our_envp);
	return (res);
}
