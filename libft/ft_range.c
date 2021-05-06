/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adconsta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 14:34:36 by adrien            #+#    #+#             */
/*   Updated: 2020/09/28 14:35:30 by adrien           ###   ########.fr       */
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
