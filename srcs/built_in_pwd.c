/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:54:26 by jacher            #+#    #+#             */
/*   Updated: 2021/04/17 10:47:38 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int 	ft_pwd(t_pipe *p, t_list **error)
{
	char	*to_write;
	(void)error;

	to_write = getcwd(NULL, 0);
	if (to_write == NULL)
		ft_putstr_fd("msh : pwd : echec getcwd\n", 2);
	//y - a t'il des cas d'erreurs a gerer?
	ft_putstr_fd(to_write, p->fd_out_to_use);
	ft_putstr_fd("\n", p->fd_out_to_use);
	free(to_write);
	g_gnl.exit_status = 0;
	//EXIT SUCCESS VALUE
	return (1);
}
