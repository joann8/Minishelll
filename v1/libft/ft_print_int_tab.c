/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:16:39 by louise            #+#    #+#             */
/*   Updated: 2020/09/28 16:32:30 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_int_tab(int *tab, int size)
{
	int	i;

	i = 0;
	write(1, "[", 1);
	while (i < size)
	{
		ft_putnbr(tab[i]);
		if (i != size - 1)
			write(1, ", ", 2);
		i++;
	}
	write(1, "]", 1);
}
