/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_factorial.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 14:21:21 by louise            #+#    #+#             */
/*   Updated: 2020/09/28 14:23:00 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_factorial(int nb)
{
	if (nb < 0)
		return (0);
	else
	{
		if (nb == 0)
			return (1);
		else
			return (ft_factorial(nb - 1) * nb);
	}
}
