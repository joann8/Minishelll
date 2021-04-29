/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 10:42:22 by calao             #+#    #+#             */
/*   Updated: 2021/04/29 10:42:24 by calao            ###   ########.fr       */
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
