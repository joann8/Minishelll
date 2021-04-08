/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 14:22:32 by louise            #+#    #+#             */
/*   Updated: 2020/09/24 12:20:42 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*mem_block;
	size_t			i;

	i = -1;
	mem_block = (unsigned char *)malloc(size * count);
	if (!(mem_block))
		return (NULL);
	while (++i < count * size)
		mem_block[i] = 0;
	return ((void *)mem_block);
}
