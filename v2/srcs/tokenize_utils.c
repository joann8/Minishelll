/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:32:59 by jacher            #+#    #+#             */
/*   Updated: 2021/04/29 19:02:11 by jacher           ###   ########.fr       */
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
	if (c == 9)
		return (1);
	if (c == 32)
		return (2);
	return (0);
}

void	escape_quote(char *str, int *pos)
{
	int i;

	i = *pos + 1;
	// ajout du ' '  pour gerer echo > test\ 1
	if (str[i] == 34 || str[i] == 39 || str[i] == ' '
		|| str[i] == '>' || str[i] == '<' || str[i] == '|'
		|| str[i] == ';')
		*pos += 1;
}

int		look_second_quote(char c, char *str, int *pos)
{
	int i;

	i = *pos + 1;
	while (str[i] && str[i] != c)
	{
		if (c == 34 && str[i] == '\\')
		{
			if (str[i + 1] == 34)
				i++;
		}
		i++;
	}
	if (str[i] != c)
		return (-1);
	*pos = i;
	return (0);
}
