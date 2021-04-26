/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_piped_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 12:41:05 by jacher            #+#    #+#             */
/*   Updated: 2021/04/26 12:00:34 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"
/*
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
}*/


int		execute_cmd_piped(t_simple_cmd *tmp_c, t_list **env, t_list **error,
			t_pipe *p)
{
/*	int		built_in_found;
	char	*job;
	int		res;

	built_in_found = find_built_in(tmp_c, error, env);
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
	return (built_in_found);//0 built in, -1 erreur built in, 227 exit*/
}
