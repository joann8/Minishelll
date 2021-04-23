/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 12:41:05 by jacher            #+#    #+#             */
/*   Updated: 2021/04/22 16:16:53 by jacher           ###   ########.fr       */
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
			|| dup2(p.fd_out_to_use, STDOUT_FILENO) == -1
			|| dup2(p.fd_err_to_use, STDERR_FILENO) == -1)
			return (-1);
		execve(job, tmp_c->av, our_envp);
		exit(255);
	}
	else
	{
		if (wait(&wstatus) == -1)
		{
			g_process.exit_status = 126;//return the status code
			return (-1);
		}
		g_process.exit_status = WEXITSTATUS(wstatus);//return the status code
	}
	return (0);//return the status code
}

int		look_for_command_and_path(char *job, t_simple_cmd *tmp_c,
			t_list **env, t_pipe p)
{
	char	**our_envp;

	our_envp = NULL;
	if ((our_envp = ft_make_ourenvp(env)) == NULL)
		return (-1);//malloc err
	if (ft_split_process(job, tmp_c, our_envp, p) == -1)//-1 pbm dup ou exec retourne -1
	{
		free_double_tab(our_envp);
		return (-1);
	}
	free_double_tab(our_envp);
	return (0);
}

int		manage_error_exec_piped(t_list **error, t_pipe *p)
{
	char *line;

	line = NULL;
	close(p->fd_tab_err[1]);
	while (get_next_line(p->fd_tab_err[0], &line) > 0)
	{
		if ((add_err_lst(error, line, "\n", NULL)) == -1)
		{
			close(p->fd_tab_err[0]);
			free(line);
			return (-1);
		}
		free(line);
	}
	close(p->fd_tab_err[0]);
	free(line);
	return (0);
}

int		execute_cmd_path_not_found(t_simple_cmd *tmp_c, t_list **error)
{
	char	*job;
	int		ret;
	int		i;
	int		path;

	job = ft_strdup(tmp_c->job);
	ret = 0;
	if (job == NULL)
		return (p_error(0, "malloc error\n", -1));
	if (errno == 2 || ((tmp_c->job[0] != '/' && tmp_c->job[0] != '.')//a revoir
			&& errno == 0))//COMMAND introuvable
	{
		i = 0;
		path = 0;
		while (job[i])
		{
			if (job[i] == '/')
				path = 1;
			i++;
		}
		g_process.exit_status = 127;
		if (path == 1)// || (tmp_c->job[0] != '/' && tmp_c->job[0] != '.')
			ret = add_err_lst(error, "msh: ", job, " : aucun fichier ou dossier de ce type\n");
		else 
			ret = add_err_lst(error,  job, " : commande introuvable\n", NULL);
	}
	else
	{
		g_process.exit_status = 126;
		ret = add_err_lst(error, "msh: ", job, " : permission denied\n");
	}
	free(job);
	return (ret);
}

int		execute_cmd(t_simple_cmd *tmp_c, t_list **env, t_list **error,
			t_pipe *p)
{
	int		built_in_found;
	char	*job;
	int		res;

	built_in_found = find_built_in(tmp_c, p, error, env);
	if (built_in_found == 1)//if different 0, execute build in in built in
	{
		job = NULL;
		res = ft_search_job_path(&job, tmp_c->job, env);
		if (res == -1)
			return (-1);//A VERFIER AVEC ADRIEN
		else if (res == 0)//cmd not found or permission denied
			return (execute_cmd_path_not_found(tmp_c, error));
		else
		{
			if (look_for_command_and_path(job, tmp_c, env, *p) == -1)
			{
				free(job);
				if ((add_err_lst(error, strerror(errno), NULL, NULL)) == -1)
					return (-1);
			}
			free(job);
			if (tmp_c->pipe_mod == 1 && tmp_c->pipe_pos != 1)
				return (manage_error_exec_piped(error, p));
			return (0);
		}
	}
	return (built_in_found);//0 built in, -1 erreur built in, 227 exit
}
