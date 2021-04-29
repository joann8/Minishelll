/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adrien <adconsta@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 12:12:31 by adrien            #+#    #+#             */
/*   Updated: 2020/09/28 16:46:02 by adrien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcapitalize(char *str)
{
	int		i;
	char	p_char;

	i = 0;
	p_char = -1;
	while (str[i])
	{
		if ((p_char == -1 || !ft_isalnum(p_char)) && ft_islowcase(str[i]))
			str[i] = ft_toupper(str[i]);
		else if (ft_isalnum(p_char) && ft_isupcase(str[i]))
			str[i] = ft_tolower(str[i]);
		p_char = str[i];
		i++;
	}
	return (str);
}
