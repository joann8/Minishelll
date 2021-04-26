/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_piped_prep.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:42:47 by jacher            #+#    #+#             */
/*   Updated: 2021/04/26 13:24:58 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	update_fd_pipes(t_simple_cmd *tmp_c, t_pipe *p, int ret)
{
//	printf("\n_____update pipe____\n");
	if (tmp_c->pipe_pos == -1)//first
	{
//		printf("**first pipe***\n");
//		printf("close fd_tab[1] =  %d\n", p->fd_tab[1]);
		close(p->fd_tab[1]);
	}
	else if (tmp_c->pipe_pos == 1)//dernier
	{
//		printf("**last pipe***\n");
//		printf("close ret = %d\n", ret);
		close(ret);
	}
	else if (tmp_c->pipe_pos == 0)
	{
//		printf("**middle pipe***\n");
		//printf("close fd_tab[1] =  %d\n", p->fd_tab[1]);
		close(p->fd_tab[1]);
	//	printf("close ret = %d\n", ret);
		close(ret);
	}
//	p->fd_in_next = p->fd_tab[0];
	if (tmp_c->fd_in != STDIN_FILENO)
	{
	//	printf("close fd_in =  %d\n", tmp_c->fd_in);
		close(tmp_c->fd_in);
	}
	if (tmp_c->fd_out != STDOUT_FILENO)
	{
	//	printf("close fd_out =  %d\n", tmp_c->fd_out);
		close(tmp_c->fd_out);
	}
//	printf("_____end update pipe____\n");
}

int		prepare_pipe_execution(t_simple_cmd *tmp_c, t_pipe *p, int ret)
{
//	printf("\n_____prepare pipe____\n");
	if (tmp_c->pipe_pos != 1)//si je suis piped mais pas le dernier
	{
		if (pipe(p->fd_tab) == -1 )//|| pipe(p->fd_tab_err) == -1)
			return (-1);
	//	printf("pipe fd_tab done for %s\n", tmp_c->job);
	//	printf("fd_tab[0] = %d | fd_tab[1] =  %d\n", p->fd_tab[0], p->fd_tab[1]);
	}
	if (tmp_c->pipe_pos == -1)//first//fd in reste le meme
	{
		if (p->fd_out_to_use == STDOUT_FILENO)
			p->fd_out_to_use = p->fd_tab[1];
		//printf("**first pipe**\n");
	//	printf("fd_in_to_use =  %d\n", p->fd_in_to_use);
	//	printf("fd_out_to_use =  %d\n", p->fd_out_to_use);
	//	printf("(ret =  %d)\n", ret);
	}
	else if (tmp_c->pipe_pos == 1)//dernier//fd out reste le meme
	{
		if (p->fd_in_to_use == STDIN_FILENO)
			p->fd_in_to_use = ret;
	//	printf("**last pipe**\n");
	//	printf("fd_in_to_use =  %d\n", p->fd_in_to_use);
	//	printf("fd_out_to_use =  %d\n", p->fd_out_to_use);
//		printf("(ret =  %d)\n", ret);
	}
	else
	{
		if (p->fd_out_to_use == STDOUT_FILENO)
			p->fd_out_to_use = p->fd_tab[1];
		if (p->fd_in_to_use == STDIN_FILENO)
			p->fd_in_to_use = ret;
	//	printf("**middle pipe**\n");
	//	printf("fd_in_to_use =  %d\n", p->fd_in_to_use);
	//	printf("fd_in_out_use =  %d\n", p->fd_out_to_use);
	//	printf("(ret =  %d)\n", ret);
	}
//	printf("_____end prepare pipe____\n");
	return (0);
}

int		execute_cmd_path_not_found_2(t_simple_cmd *tmp_c, t_list **error)
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
		g.exit_status = 127;
		if (path == 1)// || (tmp_c->job[0] != '/' && tmp_c->job[0] != '.')
			ret = add_err_lst(error, "msh: ", job, " : aucun fichier ou dossier de ce type\n");
		else 
			ret = add_err_lst(error,  job, " : commande introuvable\n", NULL);
	}
	else
	{
		g.exit_status = 126;
		ret = add_err_lst(error, "msh: ", job, " : permission denied\n");
	}
	free(job);
	return (ret);
}

int		find_cmd_piped(t_simple_cmd *tmp_c, t_list **env, t_list **error)
{
	int		built_in_found;
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
			return (execute_cmd_path_not_found_2(tmp_c, error));
		else
			return(1080);
	}
	return (built_in_found);//0 built in, -1 erreur built in, 227 exit*/
}

int			execute_piped(t_simple_cmd *begin, t_list **env, t_list **error, int size)
{
	int res;
	t_simple_cmd *tmp_c;
	res = 0;
	int	*pid_list;
	int i;	
	int wstatus;
	char *job;
	char	**our_envp;
	int 	ret;
	int 	prev;

	our_envp = NULL;
	if ((our_envp = ft_make_ourenvp(env)) == NULL)
		return (-1);//malloc err
	pid_list = malloc(sizeof(int) * size);
	if (pid_list == NULL)
		return(p_error(0, "error malloc\n", -1));
	i = 0;
	tmp_c = begin; 
	tmp_c->p.fd_in_next = -1;
	ret = -1;
	while (tmp_c)
	{
		prepare_pipe_execution(tmp_c, &(tmp_c->p), ret);
		pid_list[i] = fork();

		if (pid_list[i] == -1)
			return (-1); //close other pipes?
		if (pid_list[i] == 0)
		{
			printf("hello from child! %i\n", i);
			printf("    tmp_c->job = %s\n", tmp_c->job);
			if (find_cmd_piped(tmp_c, env, error) != 1080)
			{
				printf("---->built in done %i\n", i);
				exit(g.exit_status);
			}
			else
			{
				printf("fd in to use = %d | i = %d\n", tmp_c->p.fd_in_to_use, i);
				printf("fd out to use = %d | i = %d\n", tmp_c->p.fd_out_to_use, i);
				if (dup2(tmp_c->p.fd_in_to_use, STDIN_FILENO) == -1
					|| dup2(tmp_c->p.fd_out_to_use, STDOUT_FILENO) == -1)
					return (-1);
			//	close(tmp_c->p.fd_tab[0]);
			//	close(tmp_c->p.fd_tab[1]);
				printf("---->exec done %d \n", i);
				execve(job, tmp_c->av, our_envp);
				exit(255);
			}
		}
		else
		{
			printf("hello from parent! %i\n", i);
			printf("    tmp_c->job = %s\n", tmp_c->job);
			prev = tmp_c->p.fd_tab[0];
		//	update_fd_pipes(tmp_c, &(tmp_c->p), ret );
			ret = prev;
			tmp_c = tmp_c->next_pipe;
			i++;
		}
	}

//protection commande non fermée
	while (i)
	{	
		if (wait(&wstatus) == -1)
		{
			g.exit_status = 126;//return the status code
			return (-1);
		}
		i--;
	}
	if (g.exit_status != 130 && g.exit_status != 131)
		g.exit_status = WEXITSTATUS(wstatus);//return the status code
	free_double_tab(our_envp);
	return (0);
}

/*

	p->fd_in_to_use = tmp_c->fd_in;//deja avec les redir
	p->fd_out_to_use = tmp_c->fd_out;//deja avec les redir
	p->fd_err_to_use = STDERR_FILENO;
	if (tmp_c->pipe_mod == 1)// si je suis piped
	{
		if (prepare_pipe_execution(tmp_c, p) == -1)//erreur fonction pipe
			return (p_error(0, strerror(errno), -1));//erreur pipe (fd_tab)
	}
	if (tmp_c->on == 1)
	{
		res = execute_cmd_piped(tmp_c, env, error, p);//COMMAND EXECUTION//0 OK, 227 exit, -1 malloc
		if (res != 0)//erreur malloc ou exit
		{
			if (res == 227)
				print_cmd_error(0, *error);
			ft_lstclear(error, free);
			if (res == -1)
				ft_putstr_fd("Error command execution\n", 2);//pas sure
		}
	}
	update_fd_pipes(tmp_c, p);
	return (res);
}
*/