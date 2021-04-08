/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 13:57:47 by louise            #+#    #+#             */
/*   Updated: 2020/09/28 14:13:06 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	base_index(char *base, char c)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	long	r_nb;
	int		sign;
	int		base_len;
	int		i;

	r_nb = 0;
	sign = 1;
	i = 0;
	base_len = ft_strlen(base);
	if (ft_check_base(base))
	{
		while (ft_isspace(str[i]))
			i++;
		while (str[i] == '-' || str[i] == '+')
			if (str[i++] == '-')
				sign *= -1;
		while (base_index(base, str[i]) != -1)
		{
			r_nb = r_nb * base_len + base_index(base, str[i]);
			i++;
		}
	}
	return (r_nb * sign);
}
