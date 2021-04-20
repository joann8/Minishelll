/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_manage_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:31:53 by jacher            #+#    #+#             */
/*   Updated: 2021/04/20 15:11:10 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	escape_within_doubles(t_expansion *exp)
{
	int i;

	i = exp->i + 1;
	if (exp->str[i] == '$' || exp->str[i] == 34 || exp->str[i] == 39
		|| exp->str[i] == '\\')
		exp->i += 1;//special character also : !
	else
	{
		if (exp->mod == 2)//a verifier si vrai ou pas
			exp->tmp[exp->j] = exp->str[exp->i];
		exp->i += 1;
		exp->j += 1;
	}
}

void	manage_quotes_help(t_expansion *exp)
{
	if (exp->quote == 39)
		exp->quote = 0;
	else if (exp->quote == 0)
		exp->quote = 39;
	else if (exp->quote == 34)
	{
		if (exp->mod == 2)//a verifier si vrai ou pas
			exp->tmp[exp->j] = exp->str[exp->i];
		exp->j += 1;
	}
}

void	manage_quotes(t_expansion *exp, char c)
{
	if (c == 34)
	{
		if (exp->quote == 34)
			exp->quote = 0;
		else if (exp->quote == 0)
			exp->quote = 34;
		else if (exp->quote == 39)
		{
			if (exp->mod == 2)//a verifier si vrai ou pas
				exp->tmp[exp->j] = exp->str[exp->i];
			exp->j += 1;
		}
	}
	else if (c == 39)
		manage_quotes_help(exp);
	exp->i += 1;
}

void	manage_escape(t_expansion *exp)
{
	if (exp->quote == 34)
		escape_within_doubles(exp);
	else if (exp->quote == 0)
		exp->i += 1;
	else if (exp->quote == 39)
	{
		if (exp->mod == 2)
			exp->tmp[exp->j] = exp->str[exp->i];
		exp->i += 1;
		exp->j += 1;
	}
	if (exp->str[exp->i] == '$')
	{
		if (exp->mod == 2)
			exp->tmp[exp->j] = exp->str[exp->i];
		exp->i += 1;
		exp->j += 1;
	}
}
