/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:32:59 by jacher            #+#    #+#             */
/*   Updated: 2021/04/09 11:01:48 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		comp(char c1, char c2)
{
	if (c1 == c2)
		return (1);
	return (0);
}

int		is_whitespace(char c)
{
	if (c == 9)//tab
		return (1);
	if (c == 32)//space
		return (2);
	return (0);
}

//fonction qui sert a eviter les escape quote dans la tokenisation
void	escape_quote(char *str, int *pos)
{
	int i;

	i = *pos + 1;
	if (str[i] == 34 || str[i] == 39)
		*pos += 1;
}

int		look_second_quote(char c, char *str, int *pos)
{
	int i;

	i = *pos + 1;
	while (str[i] && str[i] != c)
	{
		if (c == 34 && str[i] == '\\')//permet d'eviter de fermer une parenthese avec un \")
		{
			if (str[i + 1] == 34)
				i++;
		}
		i++;
	}
	if (str[i] != c)
		return (-1); //erreur quote non fermée
	*pos = i;
	return (0);
}
