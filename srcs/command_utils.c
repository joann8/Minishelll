/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 12:41:05 by jacher            #+#    #+#             */
/*   Updated: 2021/05/05 09:39:34 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		execute_cmd_path_not_found_bis(t_simple_cmd *tmp_c, char *job)
{
	int	i;
	int	path;

	i = 0;
	path = 0;
	while (job[i])
	{
		if (job[i] == '/')
			path = 1;
		i++;
	}
	g_msh.exit_status = 127;
	if (path == 1)
		return (print_err_pipe("msh: ", job,
			" : no such file or directory\n", g_msh.exit_status));
	else if (ft_strcmp(job, "") == 0 && ft_strcmp(tmp_c->job, "\"\"") != 0)
		return ((g_msh.exit_status = 0));
	else
		return (print_err_pipe(job, ": command not found\n",
				NULL, g_msh.exit_status));
}

int		execute_cmd_path_not_found(t_simple_cmd *tmp_c, int ret)
{
	char	*job;

	if ((job = ft_strdup(tmp_c->av[0])) == NULL)
		return (p_error(0, "malloc error\n", -1));
	if (errno == 2 || ((tmp_c->av[0][0] != '/' && tmp_c->av[0][0] != '.')
			&& errno == 0))
		ret = execute_cmd_path_not_found_bis(tmp_c, job);
	else if (ft_strcmp(job, ".") == 0)
	{
		g_msh.exit_status = 2;
		ret = print_err_pipe("msh: ", ".: ", "not enough argument\n", 2);
	}
	else if (ft_strcmp(job, "..") == 0)
	{
		g_msh.exit_status = 127;
		ret = print_err_pipe(job, ": command not found\n", NULL, 127);
	}
	else
	{
		g_msh.exit_status = 126;
		ret = print_err_pipe("msh: ", job, ": permission denied\n", 126);
	}
	free(job);
	return (ret);
}
