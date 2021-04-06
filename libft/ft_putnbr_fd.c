/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 14:30:08 by jacher            #+#    #+#             */
/*   Updated: 2020/11/19 14:30:14 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_putnbr_rec(unsigned int nb, int fd)
{
	char	c;

	if (nb > 9)
		ft_putnbr_rec(nb / 10, fd);
	c = (nb % 10) + '0';
	write(fd, &c, 1);
}

void			ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;

	if (n < 0)
	{
		write(fd, "-", 1);
		nb = -n;
	}
	else
		nb = n;
	ft_putnbr_rec(nb, fd);
}
