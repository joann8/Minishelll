/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_piped.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:42:47 by jacher            #+#    #+#             */
/*   Updated: 2021/04/27 12:25:53 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		find_cmd_piped(char **job, t_simple_cmd *tmp_c, t_list **env, t_list **error)
{
	int		built_in_found;
	int		res;

	built_in_found = find_built_in(tmp_c, error, env);
	if (built_in_found == 1)//if different 0, execute build in in built in
	{
		res = ft_search_job_path(job, tmp_c->job, env);
		if (res == -1)
			return (-1);//A VERFIER AVEC ADRIEN
		else if (res == 0)//cmd not found or permission denied
			return (execute_cmd_path_not_found(tmp_c, error));
		else
			return(1080);
	}
	return (built_in_found);//0 built in, -1 erreur built in, 227 exit*/
}

int		execute_main_process(int ***fd_pipe, int size)
{
	int		i;
	int		wstatus;

	close_fd_pipe(fd_pipe, size);
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

int			execute_cmd_piped(t_simple_cmd *begin, char **our_envp, t_list **env,  t_list **error, int size, int ***fd_pipe)
{
	t_simple_cmd	*tmp_c;
	int				pid_list[size];
	int				i;	
	char 			*job;

	i = 0;
	tmp_c = begin; 
	while (i < size && tmp_c)
	{
		if ((pid_list[i] = fork()) == -1)
			return (-1); //close other pipes?
		if (pid_list[i] == 0)
		{
			if (set_up_child_pipes(tmp_c, size, fd_pipe, i) == -1)
				return (-1);
			job = NULL;
			if (find_cmd_piped(&job, tmp_c, env, error) != 1080)
				exit(g.exit_status);
			else
			{	
				execve(job, tmp_c->av, our_envp);
				exit(255);
			}
		}
		tmp_c = tmp_c->next_pipe;
		i++;
	}
	return ((execute_main_process(fd_pipe, size)));
}

int			execute_piped(t_simple_cmd *begin, t_list **env, t_list **error, int size)
{
	char	**our_envp;
	int		**fd_pipe;
	int		res;

	our_envp = NULL;
	if ((our_envp = ft_make_ourenvp(env)) == NULL)
		return (-1);//malloc err	
	fd_pipe = NULL;
	if (prepare_fd_pipe(&fd_pipe, size) == -1)
	{
		free_double_tab(our_envp);
		return (-1);
	}
	res = execute_cmd_piped(begin, our_envp, env, error, size, &fd_pipe);
	clear_fd_pipe(&fd_pipe, size);
	free_double_tab(our_envp);
	return (res);
}
