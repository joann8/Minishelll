/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 12:41:05 by jacher            #+#    #+#             */
/*   Updated: 2021/04/14 19:15:15 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"


int		execute_cmd(t_list *cmd_list, char **envp)
{
	t_list			*tmp_l;
	t_simple_cmd	*tmp_c;
	char			*job;
	int				pid;
	t_list			*error;

	error = NULL;
	tmp_l = cmd_list;
	while(tmp_l)
	{
		tmp_c = (t_simple_cmd *)tmp_l->content;
		//tmp_c->retour = 0; >> comment le modifier?
		//if job ) buildin
			//start buildin/
		//else
		//{
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
					if (dup2(tmp_c->fd_in, STDIN_FILENO) == -1)
						return (-1);
					//close(tmp_c->fd_in);
					if (dup2(tmp_c->fd_out, STDOUT_FILENO) == -1)
						return (-1);
					//close(tmp_c->fd_out);
					execve(job, tmp_c->av, envp);
					//gérer erreur execve
				}
				else
					wait(NULL);
			}
			if (tmp_c->last == 1)
			{
				print_cmd_error(0, error);
				ft_lstclear(&error, free);
			}
		//}
		tmp_l = tmp_l->next;
	}
	return (0);
}
