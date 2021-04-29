/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adconsta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:16:39 by adrien            #+#    #+#             */
/*   Updated: 2020/09/28 16:32:30 by adrien           ###   ########.fr       */
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
