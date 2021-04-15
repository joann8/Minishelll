/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 12:41:05 by jacher            #+#    #+#             */
/*   Updated: 2021/04/15 20:35:16 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		execute_cmd(t_list *cmd_list, char **envp)
{
	t_list			*tmp_l;
	t_simple_cmd	*tmp_c;
	char			*job;
	pid_t			pid;
	t_list			*error;
	int				fd_tab[2];
	int				fd_in_to_use;
	int				fd_out_to_use;
	int				fd_in_next;

	error = NULL;
	tmp_l = cmd_list;
	int i;
	i = 0;
	fd_in_next = -1;
	while(tmp_l)
	{
		tmp_c = (t_simple_cmd *)tmp_l->content;
		//tmp_c->retour = 0; >> comment le modifier?
		fd_in_to_use = tmp_c->fd_in;//deja avec les redir	
		fd_out_to_use = tmp_c->fd_out;//deja avec les redir
	
		//preparation pipe
		if (tmp_c->pipe_mod == 1)// si je suis piped
		{
			if (tmp_c->pipe_pos != 1)//si je suis piped mais pas le dernier
			{
				if(pipe(fd_tab) == -1)
					return (-1);//erreur
			//	printf("\n-------\nfd_tab[0] = %d | fd_tab[1] = %d\n", fd_tab[0], fd_tab[1]);
			}
			if (tmp_c->pipe_pos == -1)//first
			{
				//fd in reste le meme
				if (fd_out_to_use == STDOUT_FILENO)
					fd_out_to_use = fd_tab[1];
			}
			else if (tmp_c->pipe_pos == 1)//dernier
			{
				if (fd_in_to_use == STDIN_FILENO)
					fd_in_to_use = fd_in_next;
				//fd out reste le meme
			}
			else
			{
				if (fd_out_to_use == STDOUT_FILENO)
					fd_out_to_use = fd_tab[1];
				if (fd_in_to_use == STDIN_FILENO)
					fd_in_to_use = fd_in_next;
			}	
		}
	//	printf("--fd in to use = %d | fd out = %d | fd next = %d--\n-------\n", fd_in_to_use, fd_out_to_use, fd_in_next);
		if (find_built_in(tmp_c, envp) == 0)
		{
			job = ft_find_cmd_path(tmp_c->job);
			if (job == NULL)
			{
				job = ft_strdup(tmp_c->job);
				if (job == NULL)
					return (-1);//erreur malloc
				ft_lstadd_back(&error, ft_lstnew((void*)(job)));
			}
		//		printf("fd[0] = %d | fd[1] = %d\n", tmp_c->fd_tab[0], tmp_c->fd_tab[1]);
			else
			{
				pid = fork();
				if (pid == -1)
					return (-1);
				if (pid == 0)
				{
		//			printf("\n****hello from child %d!*****\n", i);
		//			printf("executinf |%s| with fd in to use = %d | fd out = %d\n", job , fd_in_to_use, fd_out_to_use);
					if (dup2(fd_in_to_use, STDIN_FILENO) == -1)
						return (-1);
					close(fd_in_to_use);
					if (dup2(fd_out_to_use, STDOUT_FILENO) == -1)
						return (-1);
				//	close(fd_out_to_use);
					execve(job, tmp_c->av, envp);
					//gérer erreur execve
				}
				else
				{
					wait(NULL);
			//		printf("\n****hello from parent %d!*****\n", i);
					if (tmp_c->pipe_mod == 1)
					{
						if (tmp_c->pipe_pos == -1)//first
						{
			//				printf("closing fd_tab[1]= %d\n", fd_tab[1]);
							close(fd_tab[1]);
						}
						else if (tmp_c->pipe_pos == 1)//dernier
						{
		//					printf("closing fd_in_next= %d\n", fd_in_next);
							close(fd_in_next);
						}
						else if (tmp_c->pipe_pos == 0)
						{
							close(fd_in_next);
		//					printf("closing fd_in_next= %d\n", fd_in_next);
							close(fd_tab[1]);
	//						printf("closing fd_tab[1]= %d\n", fd_tab[1]);
						}
						fd_in_next = fd_tab[0];
					}
				
				}
			}
			if (tmp_c->pipe_pos == 1)
			{
				print_cmd_error(0, error);
				ft_lstclear(&error, free);
			}
		}
		if (tmp_c->fd_in != STDIN_FILENO)
		{
			close(tmp_c->fd_in);
			printf("closing tmp_c->fd_in= %d\n", tmp_c->fd_in);
		}
		if (tmp_c->fd_out != STDOUT_FILENO)
		{
			close(tmp_c->fd_out);
			printf("closing tmp_c->fd_out= %d\n", tmp_c->fd_out);
		}
		tmp_l = tmp_l->next;
		i++;
	}
	return (0);
}
