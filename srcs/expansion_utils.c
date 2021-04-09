/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:32:59 by jacher            #+#    #+#             */
/*   Updated: 2021/04/09 13:30:15 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

//a metachar is a char that separates words when unquoted
int 	is_metachar(char c)
{
	if (c == '|' || c == '>' || c == '<' || c ==  ';')
		return (1); //operator
	if (is_whitespace(c) == 1)
		return (2); //white space
	if (c == ',' || c == '&')//addtional op, not sure
		return (3);
	return (0);
}

//a word is a sequence of char treated as a unit, without any metachar
int		is_word(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isprint(str[i]) == 1 && is_metachar(c) == 0)//a verifier ce qui constitue un mot)
			i++;
		else
			return (0);
	}
	return (1);
}

//a name is a word consisting solely of letters, numbers and underscores, starting woth letter or underscore
int		is_name(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && (ft_isalpha(str[i]) || str[i] == '_')
			i++;
		else if (ft_isalnum(str[i]) == 1 || str[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}
