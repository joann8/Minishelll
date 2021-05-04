/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 15:28:48 by jacher            #+#    #+#             */
/*   Updated: 2021/05/02 21:32:55 by calao            ###   ########.fr       */
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
	if (ft_strcmp(cmd->av[0], "echo") == 0)
		g_msh.exit_status = ft_echo(cmd, &(cmd->p), 0, 0);
	else if (ft_strcmp(cmd->av[0], "pwd") == 0)
		g_msh.exit_status = ft_pwd(&(cmd->p));
	else if (ft_strcmp(cmd->av[0], "exit") == 0)
	{
		g_msh.exit_status = ft_exit(cmd, &(cmd->p));
		return (227);
	}
	else if (ft_strcmp(cmd->av[0], "env") == 0)
		g_msh.exit_status = ft_env(env, cmd->p.fd_out_to_use);
	else if (ft_strcmp(cmd->av[0], "unset") == 0)
		g_msh.exit_status = ft_unset(cmd, env, cmd->av);
	else
		res = 1;
	if (res == 0 && g_msh.exit_status == -1)
	{
		g_msh.exit_status = 1;
		return (-1);
	}
	return (res);
}

int		find_built_in(t_simple_cmd *cmd, t_list **env)
{
	if (ft_strcmp(cmd->av[0], "cd") == 0)
	{
		g_msh.exit_status = ft_cd(cmd, env);
		if (g_msh.exit_status == -1)
		{
			g_msh.exit_status = 1;
			return (-1);
		}
		return (0);
	}
	if (ft_strcmp(cmd->av[0], "export") == 0)
	{
		g_msh.exit_status = ft_export(env, cmd, cmd->p.fd_out_to_use);
		if (g_msh.exit_status == -1)
		{
			g_msh.exit_status = 1;
			return (-1);
		}
		return (0);
	}
	else
		return (find_built_in_2(cmd, env));
}
