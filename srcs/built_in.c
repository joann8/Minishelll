/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:28:48 by jacher            #+#    #+#             */
/*   Updated: 2021/04/20 11:06:34 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		ft_env(t_list **env, int fd_out)
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
	return (0);
}

int		find_built_in_2(t_simple_cmd *cmd, t_pipe *p, t_list **env, t_list **error)
{
	if (ft_strcmp(cmd->job, "echo") == 0)
	{
		g_process.exit_status = ft_echo(cmd, p, 0, 0);
		return(1);
	}
	if (ft_strcmp(cmd->job, "pwd") == 0)
	{
		g_process.exit_status = ft_pwd(p, error);
		return (1);
	}
	if (ft_strcmp(cmd->job, "exit") == 0)
	{
		g_process.exit_status = ft_exit(cmd, p, error);
		return (1);
	}
	if (ft_strcmp(cmd->job, "env") == 0)//ADRIEN
	{
		g_process.exit_status = ft_env(env, p->fd_out_to_use);
		return (1);
	}
	if (ft_strcmp(cmd->job, "unset") == 0)//ADRIEN
	{
		g_process.exit_status = ft_unset(env, cmd->av, cmd->pipe_mod);
		return (1);
	}
	return (0);
}

int		find_built_in(t_simple_cmd *cmd, t_pipe *p, t_list **error, t_list **env)
{
	if (ft_strcmp(cmd->job, "cd") == 0)//ADRIEN
	{
		g_process.exit_status = ft_cd(cmd->av, env);
		if (g_process.exit_status == -1)
		{
			g_process.exit_status = 1;
			return (-1);
		}
		return (1);
	}
	if (ft_strcmp(cmd->job, "export") == 0)//ADRIEN
	{
		g_process.exit_status = ft_export(env, cmd->av, p->fd_out_to_use, cmd->pipe_mod); 
		if (g_process.exit_status == -1)
		{
			g_process.exit_status = 1;
			return (-1);
		}
		return (1);
	}
	else
		return (find_built_in_2(cmd, p, env, error));
}
