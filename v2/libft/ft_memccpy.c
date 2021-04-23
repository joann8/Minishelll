/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 13:07:06 by louise            #+#    #+#             */
/*   Updated: 2020/09/24 11:39:29 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	uc;
	unsigned char	*src_uc;

	i = -1;
	uc = (unsigned char)c;
	src_uc = (unsigned char*)src;
	while (++i < n)
	{
		*(unsigned char*)(dst + i) = src_uc[i];
		if (src_uc[i] == uc)
			return ((void *)(dst + i + 1));
	}
	return (NULL);
}
