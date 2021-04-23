/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:54:26 by jacher            #+#    #+#             */
/*   Updated: 2021/04/20 13:49:51 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		ft_pwd(t_pipe *p, t_list **error)
{
	char	*to_write;
	t_list	*new;
	char	*str;
	to_write = getcwd(NULL, 0);
	if (to_write == NULL)
	{
		str = ft_strdup("msh : pwd : echec getcwd\n");
		if (str == NULL)
			return (-1);
		new = ft_lstnew(str);
		if (new == NULL)
		{
			free(str);
			return (-1);
		}
		ft_lstadd_back(error, new);
		return (1);// pas sure que l'on doit quit
	}
	ft_putstr_fd(to_write, p->fd_out_to_use);
	ft_putstr_fd("\n", p->fd_out_to_use);
	free(to_write);
	return (0);
}
