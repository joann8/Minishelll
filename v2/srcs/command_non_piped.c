/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_non_piped.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 12:41:05 by jacher            #+#    #+#             */
/*   Updated: 2021/04/29 18:21:37 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		ft_split_process(char *job, t_simple_cmd *tmp_c, char **our_envp,
			t_pipe p)
{
	int		pid;
	int		wstatus;

	if ((pid = fork()) == -1)
		return (-1);
	if (pid == 0)
	{
		if (dup2(p.fd_in_to_use, STDIN_FILENO) == -1
			|| dup2(p.fd_out_to_use, STDOUT_FILENO) == -1)
			return (print_err(strerror(errno), "\n", NULL, -1));
		if (execve(job, tmp_c->av, our_envp) == -1)
			print_err(strerror(errno), "\n", NULL, -1);
		exit(255);
	}
	else
	{
		if (wait(&wstatus) == -1)
		{
			g.exit_status = 126;//return the status code
			return (-1);
		}
		if (g.exit_status != 130 && g.exit_status != 131)
			g.exit_status = WEXITSTATUS(wstatus);//return the status code
	}
	return (0);//return the status code
}

int		look_for_command_and_path(char *job, t_simple_cmd *tmp_c,
			t_list **env, t_pipe p)
{
	char	**our_envp;

	our_envp = NULL;
	if ((our_envp = ft_make_ourenvp(env)) == NULL)
		return (p_error(0, "malloc error\n", -1));
	if (ft_split_process(job, tmp_c, our_envp, p) == -1)//-1 pbm dup ou exec retourne -1
	{
		free_double_tab(our_envp);
		return (-1);
	}
	free_double_tab(our_envp);
	return (0);
}

int		execute_cmd_non_piped(t_simple_cmd *tmp_c, t_list **env)
{
	int		built_in_found;
	char	*job;
	int		res;

	built_in_found = find_built_in(tmp_c, env);
	if (built_in_found == 1)//if different 0, execute build in in built in
	{
		job = NULL;
		res = ft_search_job_path(&job, tmp_c->av[0], env);
		if (res == -1)
			return (-1);
		else if (res == 0)//cmd not found or permission denied
			return (execute_cmd_path_not_found(tmp_c, 0));
		else
		{
			res = look_for_command_and_path(job, tmp_c, env, tmp_c->p);
			free(job);
			return (0);
		}
	}
	return (built_in_found);//0 built in, -1 erreur built in, 227 exit
}

int		execute_non_piped(t_simple_cmd *tmp_c, t_list **env)
{
	int res;

	res = 0;
	tmp_c->p.fd_in_to_use = tmp_c->fd_in;//deja avec les redir
	tmp_c->p.fd_out_to_use = tmp_c->fd_out;//deja avec les redir
	res = execute_cmd_non_piped(tmp_c, env);//COMMAND EXECUTION//0 OK, 227 exit, -1 malloc
	if (res == -1)
		ft_putstr_fd("Error command execution\n", 2);//pas sure
	return (res);
}
