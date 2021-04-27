/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_piped.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:42:47 by jacher            #+#    #+#             */
/*   Updated: 2021/04/27 17:01:47 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		find_cmd_piped(t_simple_cmd *tmp_c, t_list **env, char **our_envp)
{
	int		built_in_found;
	int		res;
	char	*job;

	if ((built_in_found = find_built_in(tmp_c, env)) == 1)//if different 0, execute build in in built in
	{
		res = ft_search_job_path(&job, tmp_c->job, env);
		if (res == -1)
			return (-1);//A VERFIER AVEC ADRIEN
		else if (res == 0)//cmd not found or permission denied
			return (execute_cmd_path_not_found(tmp_c));
		else
		{
			if (execve(job, tmp_c->av, our_envp) == -1)
				print_err(strerror(errno), NULL, NULL, 0);
			free(job);
			exit(255);
		}
	}
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
			return (-1);
		if (pid_list[i] == 0)
		{
			if (set_up_child_pipes(tmp_c, begin->p.size, &fd_pipe, i) == -1)
				return (-1);
			exit(find_cmd_piped(tmp_c, env, our_envp));
		}
		tmp_c = tmp_c->next_pipe;
		i++;
	}
//	print_cmd_error(0, **error);
//	ft_lstclear(*free);
	return ((execute_main_process(&fd_pipe, begin->p.size)));
}

int		execute_piped(t_simple_cmd *begin, t_list **env)
{
	char	**our_envp;
	int		res;

	our_envp = NULL;
	if ((our_envp = ft_make_ourenvp(env)) == NULL)
		return (-1);//malloc err
	res = execute_cmd_piped(begin, our_envp, env);
	free_double_tab(our_envp);
	//print_cmd_error(0, *error);
	//ft_lstclear(free);
	return (res);
}
