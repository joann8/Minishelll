/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 10:37:04 by jacher            #+#    #+#             */
/*   Updated: 2020/11/11 11:10:14 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	car;
	unsigned char	*src;

	i = 0;
	car = (unsigned char)c;
	src = (unsigned char*)s;
	while (i < n)
	{
		src[i] = car;
		i++;
	}
	return (s);
}
