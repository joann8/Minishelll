/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 12:41:05 by jacher            #+#    #+#             */
/*   Updated: 2021/04/29 18:19:43 by jacher           ###   ########.fr       */
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
	g.exit_status = 127;
	if (path == 1)// || (tmp_c->job[0] != '/' && tmp_c->job[0] != '.')
		return (print_err("msh: ", job,
			" : no such file or directory\n", 0));
	else if (ft_strcmp(job, "") == 0 && ft_strcmp(tmp_c->job, "\"\"") != 0)//si je suis une variable non trouvée
		return ((g.exit_status = 0));
	else
		return (print_err(job, ": command not found\n", NULL, 0));
}

int		execute_cmd_path_not_found(t_simple_cmd *tmp_c, int ret)
{
	char	*job;

	job = ft_strdup(tmp_c->av[0]);
	if (job == NULL)
		return (p_error(0, "malloc error\n", -1));
	if (errno == 2 || ((tmp_c->av[0][0] != '/' && tmp_c->av[0][0] != '.')//a revoir
			&& errno == 0))//COMMAND introuvable
		ret = execute_cmd_path_not_found_bis(tmp_c, job);
	else if (ft_strcmp(job, ".") == 0)
	{
		g.exit_status = 2;
		return (print_err("msh: ", ".: ", "not enough argument\n", 0));
	}
	else if (ft_strcmp(job, "..") == 0)
	{
		g.exit_status = 127;
		return (print_err(job, ": command not found\n", NULL, 0));
	}
	else
	{
		g.exit_status = 126;
		ret = print_err("msh: ", job, ": permission denied\n", 0);
	}
	free(job);
	return (ret);
}
