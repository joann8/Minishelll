/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 13:37:31 by louise            #+#    #+#             */
/*   Updated: 2020/09/29 20:42:53 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	putnbr_rec(unsigned long nb, char *base, int base_len)
{
	char	digit;

	if (nb >= (unsigned long)base_len)
		putnbr_rec(nb / (base_len), base, base_len);
	digit = base[nb % base_len];
	write(1, &digit, 1);
}

void	ft_putnbr_base(long nbr, char *base)
{
	int				base_len;
	unsigned long	nb;

	base_len = ft_strlen(base);
	if (ft_check_base(base))
	{
		if (nbr < 0)
		{
			write(1, "-", 1);
			nb = - (unsigned long) nbr;
		}
		else
			nb = nbr;
		putnbr_rec(nb, base, base_len);
	}
}
