/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_manage.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:31:53 by jacher            #+#    #+#             */
/*   Updated: 2021/04/22 10:10:54 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		manage_special_exit_help(t_expansion *exp)
{
	int k;

	exp->var_str = ft_itoa(g_process.exit_status);
	if (exp->var_str == NULL)
		return (p_error(0, "malloc error\n", -1));
	exp->i += 2;
	k = 0;
	while (exp->var_str[k])
	{
		exp->tmp[exp->j] = exp->var_str[k];
		exp->j += 1;
		k++;
	}
	free(exp->var_str);
	return (0);
}

int		manage_special_exit(t_expansion *exp)
{
	int		res;
	char	*tmp;

	if (exp->mod == 1)
	{
		tmp = ft_itoa(g_process.exit_status);
		if (tmp == NULL)
			return (p_error(0, "malloc error\n", -1));
		res = ft_strlen(tmp);
		free(tmp);
		exp->j += res;
		exp->i += 1;
	}
	else if (exp->mod == 2)
	{
		if (manage_special_exit_help(exp) == -1)
			return (-1);
	}
	return (0);
}

int		manage_special_backslash(t_expansion *exp)
{
	if (exp->mod == 1)
	{
		exp->j += 1;
		exp->i += 2;
		if (exp->quote == 34)
			exp->j += 1;
	}
	if (exp->mod == 2)
	{
		exp->tmp[exp->j] = exp->str[exp->i];
		exp->j += 1;
		exp->i += 1;
		if (exp->quote == 34)
		{
			exp->tmp[exp->j] = exp->str[exp->i];
			exp->j += 1;
		}
		exp->i += 1;
	}
	return (0);
}

int		manage_variable_help(t_expansion *exp, t_list *var, int k)
{
	int res;

	if (exp->mod == 1)
	{
		res = find_variable_length(exp->str, exp->i + 1, k - 1, var);
		if (res == -1)
			return (-1);
		exp->j += res;
		exp->i = k;
	}
	else if (exp->mod == 2)
	{
		exp->var_str = find_variable_str(exp->str, exp->i + 1, k - 1, var);
		if (exp->var_str == NULL)
			return (p_error(0, "malloc error\n", -1));
		exp->i = k;
		k = 0;
		while (exp->var_str[k])
		{
			exp->tmp[exp->j] = exp->var_str[k];
			exp->j += 1;
			k++;
		}
	}
	return (0);
}

int		manage_variable(t_expansion *exp, t_list *var)
{
	int k;

	k = exp->i + 1;
	if (exp->str[k] == '?')
		return (manage_special_exit(exp));
	if (exp->str[k] == '\\')
		return (manage_special_backslash(exp));
	if (is_var_name(exp->str[k], 0) == 1)
		while (is_var_name(exp->str[k], 1) == 1)
			k++;
	else
	{
		exp->i = k + 1;
		return (0);
	}
	return (manage_variable_help(exp, var, k));
}
