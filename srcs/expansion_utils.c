/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:32:59 by jacher            #+#    #+#             */
/*   Updated: 2021/04/20 15:23:58 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	ft_copy_loc_expansion(char *tofind, char *str, int start, int end)
{
	int i;

	i = 0;
	while (start + i <= end)
	{
		tofind[i] = str[start + i];
		i++;
	}
	tofind[i] = '\0';
}

int		is_metachar(char c)
{
	//a metachar is a char that separates words when unquoted
	if (c == '|' || c == '>' || c == '<' || c == ';')
		return (1);//operator
	if (is_whitespace(c) == 1)
		return (2);//white space
	if (c == ',' || c == '&')//addtional op, not sure
		return (3);
	return (0);
}

int		is_word(char *str)
{
	int i;

	//a word is a sequence of char treated as a unit, without any metachar
	i = 0;
	while (str[i])
	{
		if (ft_isprint(str[i]) == 1 && is_metachar(str[i]) == 0)
			i++;
		else
			return (0);
	}
	return (1);
}

int		is_name(char *str)
{
	int i;

	//a name is a word consisting solely of letters, numbers and underscores
	//starting woth letter or underscore
	i = 0;
	while (str[i])
	{
		if (i == 0 && (ft_isalpha(str[i]) || str[i] == '_'))
			i++;
		else if (i > 0 && (ft_isalnum(str[i]) == 1 || str[i] == '_'))
			i++;
		else
			return (0);
	}
	return (1);
}

int		is_var_name(char c, int mod)
{
	if (mod == 0)//checker 1re lettre
	{
		if (ft_isalpha(c) == 1 || c == '_')
			return (1);
	}
	if (mod == 1)//checker milieu
	{
		if (ft_isalnum(c) == 1 || c == '_')
			return (1);
	}
	return (0);
}
