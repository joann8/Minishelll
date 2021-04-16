/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:54:26 by jacher            #+#    #+#             */
/*   Updated: 2021/04/16 18:09:15 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int 	ft_pwd(t_simple_cmd *cmd, t_pipe *p, t_list **error, t_list **env)
{
	char	*to_write;

	to_write = getcwd(NULL, 0);
	if (to_write == NULL)
		ft_putstr_fd(2, "msh : pwd : echec getcwd\n");
	//y - a t'il des cas d'erreurs a gerer?
	fd_putstr_fd(p->fd_out_to_use, to_write);
	ft_putstr_fd(p->fd_out_to_use, "\n");
	free(to_write);
	g_gnl.exit_status = 0;
	//EXIT SUCCESS VALUE
	return (1);
}
