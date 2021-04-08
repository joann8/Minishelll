/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 18:32:26 by louise            #+#    #+#             */
/*   Updated: 2020/12/23 21:47:08 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	itoa_count_char(int n)
{
	int		nb_char;
	long	nb;

	nb_char = 1;
	if (n < 0)
		nb_char = 2;
	nb = n;
	if (n < 0)
		nb = - (long) n;
	while (nb / 10 != 0)
	{
		nb_char++;
		nb /= 10;
	}
	return (nb_char);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		nb_char;
	long	abs_n;

	nb_char = itoa_count_char(n);
	abs_n = n;
	if (n < 0)
		abs_n = - (long) n;
	str = (char*)malloc(sizeof(char) * (nb_char + 1));
	if (!str)
		return (NULL);
	str[nb_char] = '\0';
	while (--nb_char >= 0)
	{
		str[nb_char] = abs_n % 10 + '0';
		abs_n /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
