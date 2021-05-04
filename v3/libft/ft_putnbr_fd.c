/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adconsta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 18:30:00 by adrien            #+#    #+#             */
/*   Updated: 2021/04/20 10:34:45 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;
	char	digit;

	nb = n;
	if (n < 0)
	{
		write(fd, "-", 1);
		nb = -(long)n;
	}
	if (nb >= 10)
		ft_putnbr_fd(nb / 10, fd);
	digit = (nb % 10) + '0';
	write(fd, &digit, 1);
}
