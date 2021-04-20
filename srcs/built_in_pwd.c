/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:54:26 by jacher            #+#    #+#             */
/*   Updated: 2021/04/20 11:30:02 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		ft_pwd(t_pipe *p, t_list **error)
{
	char	*to_write;

	to_write = getcwd(NULL, 0);
	if (to_write == NULL)
	{
		ft_lstadd_back(error,
			ft_lstnew(ft_strdup("msh : pwd : echec getcwd\n")));
		return (1);// pas sure que l'on doit quit
	}
	ft_putstr_fd(to_write, p->fd_out_to_use);
	ft_putstr_fd("\n", p->fd_out_to_use);
	free(to_write);
	return (0);
}
