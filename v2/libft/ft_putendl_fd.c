/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 18:21:52 by louise            #+#    #+#             */
/*   Updated: 2020/10/09 22:19:53 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int		len;
	char	c_endl;

	len = 0;
	if (s)
		len = ft_strlen(s);
	c_endl = '\n';
	write(fd, s, len);
	write(fd, &c_endl, 1);
}
