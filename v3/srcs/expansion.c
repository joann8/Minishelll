/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:31:53 by jacher            #+#    #+#             */
/*   Updated: 2021/05/04 14:41:22 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		init_modify_str(t_expansion *exp, char *str, int *size, t_list **var)
{
	exp->str = str;
	exp->tmp = NULL;
	exp->var_str = NULL;
	*size = count_final_str(exp, *var);
	if (*size == -1)
		return (-1);
	return (0);
}

char	*modify_str(char *str, t_list **var)
{
	char		*tmp;
	int			size;
	t_expansion	exp;

	if (init_modify_str(&exp, str, &size, var) == -1)
		return (NULL);
	if (size == 0)
	{
		if ((tmp = ft_strdup("")) == NULL)
			p_error(0, "malloc error\n", -1);
		return (tmp);
	}
	if ((exp.tmp = malloc(sizeof(char) * (size + 1))) == NULL)
	{
		p_error(0, "malloc error\n", -1);
		return (NULL);
	}
	if (ft_strcmp(str, "$") == 0)
	{
		free(exp.tmp);
		tmp = ft_strdup("$");
	}
	else
		tmp = assign_final_str(&exp, *var);
	return (tmp);
}
