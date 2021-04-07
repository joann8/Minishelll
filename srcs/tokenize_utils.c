/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:32:59 by jacher            #+#    #+#             */
/*   Updated: 2021/04/07 16:10:18 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		is_specific(char c1, char c2)
{
	if (c1 == c2)
		return(1);
	return (0);
}

int		is_whitespace(char c)
{
	if (c == '\n')
		return (1);
	if (c == 9)//tab
		return (2);
	if (c == 32)//space
		return (3);
	return (0);
}

int		is_word(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isprint(str[i]) == 1)//a verifier ce qui constitue un mot)
			i++;
		else
			return (0);
	}
	return (1);
}

int		look_second_quote(char c, char *str, int *pos)
{
	int i;

	i = *pos + 1;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] != c)
		return (-1); //erreur quote non fermée
	*pos = i;
	return (0);
}
