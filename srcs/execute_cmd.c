/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 12:41:05 by jacher            #+#    #+#             */
/*   Updated: 2021/04/20 12:00:16 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	update_fd_pipes(t_simple_cmd *tmp_c, t_pipe *p)
{
	if (tmp_c->pipe_mod == 1)
	{
		if (tmp_c->pipe_pos == -1)//first
			close(p->fd_tab[1]);
		else if (tmp_c->pipe_pos == 1)//dernier
			close(p->fd_in_next);
		else if (tmp_c->pipe_pos == 0)
		{
			close(p->fd_in_next);
			close(p->fd_tab[1]);
		}
		p->fd_in_next = p->fd_tab[0];
	}
	if (tmp_c->fd_in != STDIN_FILENO)
		close(tmp_c->fd_in);
	if (tmp_c->fd_out != STDOUT_FILENO)
		close(tmp_c->fd_out);
}

int		prepare_pipes(t_simple_cmd *tmp_c, t_pipe *p) 
{
	if (tmp_c->pipe_pos != 1)//si je suis piped mais pas le dernier
	{
		if(pipe(p->fd_tab) == -1)
			return (-1);//erreur
		//	printf("\n-------\nfd_tab[0] = %d | fd_tab[1] = %d\n", fd_tab[0], fd_tab[1]);
	}
	if (tmp_c->pipe_pos == -1)//first
	{
		//fd in reste le meme
		if (p->fd_out_to_use == STDOUT_FILENO)
			p->fd_out_to_use = p->fd_tab[1];
	}
	else if (tmp_c->pipe_pos == 1)//dernier
	{
		if (p->fd_in_to_use == STDIN_FILENO)
			p->fd_in_to_use = p->fd_in_next;
		//fd out reste le meme
	}
	else
	{
		if (p->fd_out_to_use == STDOUT_FILENO)
			p->fd_out_to_use = p->fd_tab[1];
		if (p->fd_in_to_use == STDIN_FILENO)
			p->fd_in_to_use = p->fd_in_next;
	}
	return (0);
}

int		ft_split_process(char *job, t_simple_cmd *tmp_c, char **our_envp, t_pipe p)
{
	pid_t	pid;
	int		wstatus;
	int		err; 

	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
//		printf("execution |%s| with fd in to use = %d | fd out = %d\n", job , fd_in_to_use, fd_out_to_use);
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

int		look_for_command_and_path(char *job, t_simple_cmd *tmp_c, t_list **env, t_pipe p)
{
	char	**our_envp;

	our_envp = NULL;
	if ((our_envp = ft_make_ourenvp(env)) == NULL)
		return (-1);//malloc err
	if (ft_split_process(job, tmp_c, our_envp, p) == -1)
	{
		free_double_tab(our_envp);
		return (-1);
	}
	free_double_tab(our_envp);
	return (0);
}

int		execute_cmd(t_simple_cmd *tmp_c, t_list **env, t_list **error, t_pipe *p)
{
	int		built_in_found;
	char	*job;
	int		res;

	built_in_found = find_built_in(tmp_c, p, error, env); //if different 0, execute build in in built in
	if (built_in_found == 0)//if different 0, execute build in in built in
	{
		job = NULL;
		res = ft_search_job_path(&job, tmp_c->job, env);
		if (res == -1)
			return (-1);//erreur malloc
		else if (res == 0)
		{
			job = ft_strdup(tmp_c->job);
			if (job == NULL)
				return (-1);
			ft_add_error_list(error, job, " : commande introuvable\n", NULL);
		}
		else
			look_for_command_and_path(job, tmp_c, env, *p);
	}
	return (0);
}
