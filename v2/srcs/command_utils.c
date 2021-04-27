/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 12:41:05 by jacher            #+#    #+#             */
/*   Updated: 2021/04/27 16:19:40 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		execute_cmd_path_not_found_bis(char *job)
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
			" : aucun fichier ou dossier de ce type\n", 0));
	else
		return (print_err(job, " : commande introuvable\n", NULL, 0));
}

int		execute_cmd_path_not_found(t_simple_cmd *tmp_c)
{
	char	*job;
	int		ret;

	ret = 0;
	job = ft_strdup(tmp_c->job);
	if (job == NULL)
		return (p_error(0, "malloc error\n", -1));
	if (errno == 2 || ((tmp_c->job[0] != '/' && tmp_c->job[0] != '.')//a revoir
			&& errno == 0))//COMMAND introuvable
		ret = execute_cmd_path_not_found_bis(job);
	else
	{
		g.exit_status = 126;
		ret = print_err("msh: ", job, " : permission denied\n", 0);
	}
	free(job);
	return (ret);
}
