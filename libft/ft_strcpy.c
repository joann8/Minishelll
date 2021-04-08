/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 00:46:27 by louise            #+#    #+#             */
/*   Updated: 2020/09/28 00:48:43 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(src);
	while (++i < len)
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}
