/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:31:53 by jacher            #+#    #+#             */
/*   Updated: 2021/04/28 22:12:30 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

char	*modify_str(char *str, t_list **var)
{
	char		*tmp;
	int			size;
	t_expansion	exp;

	exp.str = str;
	exp.tmp = NULL;
	exp.var_str = NULL;
	size = count_final_str(&exp, *var);
	if (size == -1)
		return (NULL);
	if (size == 0)
	{
		if ((tmp = ft_strdup("")) == NULL)
			p_error(0, "malloc error\n", -1);
		return (tmp);
	}
	exp.tmp = malloc(sizeof(char) * (size + 1));
	if (exp.tmp == NULL)
	{
		p_error(0, "malloc error\n", -1);
		return (NULL);
	}
	if (ft_strcmp(str, "$") == 0)
		tmp = ft_strdup("$");
	else
		tmp = assign_final_str(&exp, *var);
	return (tmp);
}
