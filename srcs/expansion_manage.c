/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_manage.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:31:53 by jacher            #+#    #+#             */
/*   Updated: 2021/04/13 11:13:35 by jacher           ###   ########.fr       */
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

int		manage_variable(t_expansion *exp, t_list *var)
{
	int k;
	int res;

	k = exp->i + 1;
//	if (exp->str[k] == '?' && is_var_name(exp->str[k + 1]) == 0)
		//manage exit status for mod 1 && mod 2
		// DEFINITION : $? expands to the exit status of the most recebtly executed foreground pipeline
//  else
//	{
	while (is_var_name(exp->str[k]) == 1)
		k++;
	if (exp->mod == 1)
	{
		res = find_variable_length(exp->str, exp->i + 1, k - 1, var);
		if (res == -1)
			return (-1);//erreur malloc
		exp->j += res;
		exp->i = k;
	}
	else if (exp->mod == 2)
	{
		exp->var_str = find_variable_str(exp->str, exp->i + 1, k - 1, var);
		if (exp->var_str == NULL)
			return (-1);//erreur malloc
		exp->i = k;
		k = 0;
		while (exp->var_str[k])
		{
			exp->tmp[exp->j] = exp->var_str[k];
			exp->j += 1;
			k++;
		}
	}
//	}
	return (0);
}
