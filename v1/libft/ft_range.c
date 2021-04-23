/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 14:34:36 by louise            #+#    #+#             */
/*   Updated: 2020/09/28 14:35:30 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_range(int min, int max)
{
	unsigned int	range_len;
	unsigned int	i;
	int				*range_tab;

	range_tab = NULL;
	if (min < max)
	{
		range_len = max - min;
		i = -1;
		range_tab = malloc(range_len * sizeof(int));
		if (!range_tab)
			return (NULL);
		while (++i < range_len)
			range_tab[i] = min + i;
	}
	return (range_tab);
}
