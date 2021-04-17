/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_by_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 12:41:05 by jacher            #+#    #+#             */
/*   Updated: 2021/04/17 14:55:52 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	update_fd_pipes(t_simple_cmd *tmp_c, t_pipe *p)
{
	if (tmp_c->pipe_mod == 1)
	{
		if (tmp_c->pipe_pos == -1)//first
		{
		//	printf("closing fd_tab[1]= %d\n", fd_tab[1]);
			close(p->fd_tab[1]);
		}
		else if (tmp_c->pipe_pos == 1)//dernier
		{
		//	printf("closing fd_in_next= %d\n", fd_in_next);
			close(p->fd_in_next);
		}
		else if (tmp_c->pipe_pos == 0)
		{
			close(p->fd_in_next);
		//	printf("closing fd_in_next= %d\n", fd_in_next);
			close(p->fd_tab[1]);
		//	printf("closing fd_tab[1]= %d\n", fd_tab[1]);
		}
		p->fd_in_next = p->fd_tab[0];
	}
	if (tmp_c->fd_in != STDIN_FILENO)
	{
		close(tmp_c->fd_in);
	//	printf("closing tmp_c->fd_in= %d\n", tmp_c->fd_in);
	}
	if (tmp_c->fd_out != STDOUT_FILENO)
	{
		close(tmp_c->fd_out);
	//	printf("closing tmp_c->fd_out= %d\n", tmp_c->fd_out);
	}
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
	pid_t pid;

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
		execve(job, tmp_c->av, our_envp);
		//gérer erreur execve
	}
	else
		wait(NULL);
	return (0);		
}

int		look_for_command_and_path(t_list **error, t_simple_cmd *tmp_c, t_list **env, t_pipe p)
{
	char *job;
	int		res;
	char	**our_envp;

	job = NULL;
	our_envp = NULL;
	res = 1;
	// RES NE FONCTIONNE PAS
	if (tmp_c->job[0] != '/' && tmp_c->job[0] != '.')// a verifier pour les point
		res = ft_find_cmd_path(&job, tmp_c->job, env);
	else
		job = ft_strdup(tmp_c->job);//a verifier erreur malloc
	if (res == -1 || (job == NULL && res != 0))
		return (-1);//erreur malloc
	else if (res == 0)
	{
		job = ft_strdup(tmp_c->job);
		if (job == NULL)
			return (-1);//erreur malloc
		ft_lstadd_back(error, ft_lstnew((void*)(job)));
	}
	else
	{
		if ((our_envp = ft_make_ourenvp(env)) == NULL)
			return (-1);//malloc err
		ft_print_str_table(our_envp);
		if (ft_split_process(job, tmp_c, our_envp, p) == -1)
		{
			free_double_tab(our_envp);
			return (-1);
		}
	free_double_tab(our_envp);
	}
	return (0);
}

int		execute_cmd_by_cmd(t_simple_cmd *tmp_c, t_list **env)
{
//	t_list			*tmp_l;
//	t_simple_cmd	*tmp_c;
	t_list			*error;
	t_pipe			p;
	int				res;

	error = NULL;
//	tmp_l = cmd_list;
	p.fd_in_next = -1;
//	while(tmp_l)
//	{
//		tmp_c = (t_simple_cmd *)tmp_l->content;
		//tmp_c->retour = 0; >> comment le modifier?
		p.fd_in_to_use = tmp_c->fd_in;//deja avec les redir	
		p.fd_out_to_use = tmp_c->fd_out;//deja avec les redir
		if (tmp_c->pipe_mod == 1)// si je suis piped
			if (prepare_pipes(tmp_c, &p) == -1)
				return (-1);
	//	printf("--fd in to use = %d | fd out = %d | fd next = %d--\n-------\n", fd_in_to_use, fd_out_to_use, fd_in_next);
		res = find_built_in(tmp_c, &p, &error, env);//if different 0, execute build in in built in
		if (res == -1)
			return (-1); //erreur malloc dans built in
		if (res == 0)//if different 0, execute build in in built in
		{
			//create_tab_env;
			look_for_command_and_path(&error, tmp_c, env, p);
			//free_env_tab;
		}
		if (tmp_c->pipe_pos == 1)// a voir avec le sbuilt in
		{
			print_cmd_error(0, error);
			ft_lstclear(&error, free);
		}
		update_fd_pipes(tmp_c, &p);
//		tmp_l = tmp_l->next;
//	}
	return (0);
}
