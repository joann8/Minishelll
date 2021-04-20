/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 12:41:05 by jacher            #+#    #+#             */
/*   Updated: 2021/04/20 20:13:02 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		ft_split_process(char *job, t_simple_cmd *tmp_c, char **our_envp,
			t_pipe p)
{
	pid_t	pid;
	int		wstatus;
	int		err;

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
//		printf("execution |%s| with fd in to use = %d | fd out = %d\n", job ,
// fd_in_to_use, fd_out_to_use);
		if (dup2(p.fd_in_to_use, STDIN_FILENO) == -1)
			return (-1);
	//	close(fd_in_to_use);
		if (dup2(p.fd_out_to_use, STDOUT_FILENO) == -1)
			return (-1);
	//	close(fd_out_to_use);
		err = execve(job, tmp_c->av, our_envp);
		if (err == -1)
		{
			printf("pbm execve %d - %s\n", errno, strerror(errno));
			kill(0, SIGKILL);
			return (-1); //erreur execution
		}
	}
	else
	{
		wait(&wstatus);
		printf("hello from parent\n");
		g_process.exit_status = WEXITSTATUS(wstatus);
	}
	return (0);
}

int		look_for_command_and_path(char *job, t_simple_cmd *tmp_c,
			t_list **env, t_pipe p)
{
	char	**our_envp;

	our_envp = NULL;
	if ((our_envp = ft_make_ourenvp(env)) == NULL)
		return (-1);//malloc err
	if (ft_split_process(job, tmp_c, our_envp, p) == -1)
	{
		g_process.exit_status = 1;//pas sure
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
	if (built_in_found == 0)//if different 0, execute build in in built in
	{
		job = NULL;
		res = ft_search_job_path(&job, tmp_c->job, env);
		if (res == -1)
			return ((g_process.exit_status = 1));//A VERFIER AVEC ADRIEN
		else if (res == 0)
		{
			job = ft_strdup(tmp_c->job);
			if (job == NULL)
				return ((g_process.exit_status = 1));//A VERFIER AVEC ADRIEN
			else if (add_err_lst(error, job,
						" : commande introuvable\n", NULL) == -1)
				return ((g_process.exit_status = 1));//A VERFIER AVEC ADRIEN
		}
		else
		{
			if (look_for_command_and_path(job, tmp_c, env, *p) == -1)
			{
				if ((add_err_lst(error, strerror(errno), NULL, NULL)) == -1)
					return ((g_process.exit_status = 1));//A VERFIER AVEC ADRIEN
			}
		}
	}
	return (0);
}
