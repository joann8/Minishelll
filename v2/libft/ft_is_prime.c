/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 14:31:04 by louise            #+#    #+#             */
/*   Updated: 2020/09/28 14:31:43 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_prime(int nb)
{
	int	nb_div;
	int	i;

	nb_div = 2;
	i = 2;
	if (nb <= 3)
		return (nb > 1);
	else if (nb % 2 == 0 || nb % 3 == 0)
		return (0);
	i = 5;
	while (i * i <= nb && i <= 46430)
	{
		if (nb % i == 0)
			nb_div++;
		i += 2;
	}
	return (nb_div == 2);
}
