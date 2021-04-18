/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:28:48 by jacher            #+#    #+#             */
/*   Updated: 2021/04/17 17:25:04 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	ft_env(t_list **env, int fd_out);

int		find_built_in(t_simple_cmd *cmd, t_pipe *p, t_list **error, t_list **env)
{
	(void)error;
	(void)env;

	if (ft_strcmp(cmd->job, "echo") == 0)
	{
		return(ft_echo(cmd, p));
	}
	if (ft_strcmp(cmd->job, "env") == 0)//ADRIEN
	{
		ft_env(env, p->fd_out_to_use);
		return (6);
	}
	if (ft_strcmp(cmd->job, "pwd") == 0)//JOANN
		return (ft_pwd(p, error));
/*
	//	if (ft_strcmp(cmd->job, "cd") == 0)//ADRIEN
//		return (2);
//		*/
	if (ft_strcmp(cmd->job, "export") == 0)//ADRIEN
	{
		ft_export(env, cmd->av, p->fd_out_to_use, cmd->pipe_mod); 
		return (4);
	}
	if (ft_strcmp(cmd->job, "unset") == 0)//ADRIEN
	{
		ft_unset(env, cmd->av, cmd->pipe_mod);
		return (5);
	}
	if (ft_strcmp(cmd->job, "exit") == 0)//JOANN
		return (ft_exit(cmd, p));
	return (0);
}

void	ft_env(t_list **env, int fd_out)
{
	t_list	*tmp;
	t_var	*var;

	tmp = *env;
	while (tmp)
	{
		var = (t_var *)tmp->content;
		if (var->on == 1)
		{
			ft_putstr_fd(var->name, fd_out);
			ft_putstr_fd("=", fd_out);
			ft_putstr_fd(var->value, fd_out);
			ft_putstr_fd("\n", fd_out);
		}
		tmp = tmp->next;
	}
}

