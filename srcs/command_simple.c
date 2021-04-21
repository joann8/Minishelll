/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 12:41:05 by jacher            #+#    #+#             */
/*   Updated: 2021/04/21 19:59:59 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		ft_split_process(char *job, t_simple_cmd *tmp_c, char **our_envp,
			t_pipe p)
{
	int		pid;
	int		wstatus;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
	//	printf("p.fd_in_to_use = %d\n", p.fd_in_to_use);
	//	printf("p.fd_out_to_use = %d\n", p.fd_out_to_use);
	//	printf("p.fd_err_to_use = %d\n", p.fd_err_to_use);
		if (dup2(p.fd_in_to_use, STDIN_FILENO) == -1)
			return (-1);
		if (dup2(p.fd_out_to_use, STDOUT_FILENO) == -1)
			return (-1);
		if (dup2(p.fd_err_to_use, STDERR_FILENO) == -1)
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
		else
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
	if (ft_split_process(job, tmp_c, our_envp, p) == -1)//pbm exec
	{
	//	g_process.exit_status = 1;//pas sure
		free_double_tab(our_envp);
		return (-1);
	}
	free_double_tab(our_envp);
	return (0);
}

int		execute_cmd(t_simple_cmd *tmp_c, t_list **env, t_list **error,
			t_pipe *p)
{
	int		built_in_found;
	char	*job;
	int		res;

	built_in_found = find_built_in(tmp_c, p, error, env);
//	printf("built in found = %d\n", built_in_found);
	if (built_in_found == 1)//if different 0, execute build in in built in
	{
		job = NULL;
		res = ft_search_job_path(&job, tmp_c->job, env);
		if (res == -1)
			return (-1);//A VERFIER AVEC ADRIEN
		else if (res == 0)
		{
			//printf("errno = %d | sterro = %s\n", errno, strerror(errno));
			job = ft_strdup(tmp_c->job);
			if (job == NULL)
				return (-1);//A VERFIER AVEC ADRIEN
			if (errno == 2)//COMMAND introuvable
			{
				g_process.exit_status = 127;
				if (add_err_lst(error, job,	" : commande introuvable\n", NULL) == -1)
				{
					free(job);
					return (-1);
				}
			}
			else
			{
				g_process.exit_status = 126;
			 	if (add_err_lst(error, job,	" : permission denied\n", NULL) == -1)
				{
					free(job);
					return (-1);
				}
			}
			free(job);
			return (0);
		}
		else
		{
			if (look_for_command_and_path(job, tmp_c, env, *p) == -1)
			{
				if ((add_err_lst(error, strerror(errno), NULL, NULL)) == -1)
					return (-1);//A VERFIER AVEC ADRIEN
			}
			if (tmp_c->pipe_mod == 1 && tmp_c->pipe_pos != 1)
			{
				char *line;
				line = NULL;
				close(p->fd_tab_err[1]);
				while (get_next_line(p->fd_tab_err[0], &line) > 0)
				{
					if ((add_err_lst(error, line, "\n", NULL)) == -1)
						break;
				}
				close(p->fd_tab_err[0]);
				//printf("line = %s\n", line); 

			}
		//	printf("return 0 here\n");
			return (0);
		}
	}
	return (built_in_found);//0 execv 1 built in -1 malloc 19
}
