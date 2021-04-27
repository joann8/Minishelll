/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 12:41:05 by jacher            #+#    #+#             */
/*   Updated: 2021/04/27 15:10:02 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		execute_cmd_path_not_found_bis(char *job, t_list ***error)
{
	int	i;
	int	path;
	int ret;

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
		ret = add_err_lst(*error, "msh: ", job,
			" : aucun fichier ou dossier de ce type\n");
	else
		ret = add_err_lst(*error, job, " : commande introuvable\n", NULL);
	print_cmd_error(0, **error);
	return (ret);
}

int		execute_cmd_path_not_found(t_simple_cmd *tmp_c, t_list ***error)
{
	char	*job;
	int		ret;

	ret = 0;
	job = ft_strdup(tmp_c->job);
	if (job == NULL)
		return (p_error(0, "malloc error\n", -1));
	if (errno == 2 || ((tmp_c->job[0] != '/' && tmp_c->job[0] != '.')//a revoir
			&& errno == 0))//COMMAND introuvable
		ret = execute_cmd_path_not_found_bis(job, error);
	else
	{
		g.exit_status = 126;
		ret = add_err_lst(*error, "msh: ", job, " : permission denied\n");
		print_cmd_error(0, **error);
	}
	free(job);
	return (ret);
}
