/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adconsta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 00:46:27 by adrien            #+#    #+#             */
/*   Updated: 2020/09/28 00:48:43 by adrien           ###   ########.fr       */
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
