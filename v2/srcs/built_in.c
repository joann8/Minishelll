/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:28:48 by jacher            #+#    #+#             */
/*   Updated: 2021/04/28 10:16:09 by calao            ###   ########.fr       */
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

int		find_built_in_2(t_simple_cmd *cmd, t_list **env)
{
	int res;

	res = 0;
	if (ft_strcmp(cmd->job, "echo") == 0)
		g.exit_status = ft_echo(cmd, &(cmd->p), 0, 0);
	else if (ft_strcmp(cmd->job, "pwd") == 0)
		g.exit_status = ft_pwd(&(cmd->p));
	else if (ft_strcmp(cmd->job, "exit") == 0)
	{
		g.exit_status = ft_exit(cmd, &(cmd->p));
		//if (cmd->pipe_mod == 0)
		return (227);
	}
	else if (ft_strcmp(cmd->job, "env") == 0)
		g.exit_status = ft_env(env, cmd->p.fd_out_to_use);
	else if (ft_strcmp(cmd->job, "unset") == 0)
		g.exit_status = ft_unset(env, cmd->av);
	else
		res = 1;
	if (res == 0 && g.exit_status == -1)
	{
		g.exit_status = 1;
			return (-1);
	}
	return (res);
}

int		find_built_in(t_simple_cmd *cmd, t_list **env)
{
	if (ft_strcmp(cmd->job, "cd") == 0)
	{
		g.exit_status = ft_cd(cmd, env);
		if (g.exit_status == -1)
		{
			g.exit_status = 1;
			return (-1);
		}
		return (0);
	}
	if (ft_strcmp(cmd->job, "export") == 0)
	{
		g.exit_status = ft_export(env, cmd, cmd->p.fd_out_to_use);
		if (g.exit_status == -1)
		{
			g.exit_status = 1;
			return (-1);
		}
		return (0);
	}
	else
		return (find_built_in_2(cmd, env));
}
