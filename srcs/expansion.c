/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:31:53 by jacher            #+#    #+#             */
/*   Updated: 2021/04/20 14:55:47 by jacher           ###   ########.fr       */
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
	if (size == 0 || size == -2)//-2 == cas variable name commencant par chiffre apr ex
		return (ft_strdup(""));
	tmp = malloc(sizeof(char) * (size + 1));
	if (tmp == NULL)
		return (NULL);
	exp.tmp = tmp;
	tmp = assign_final_str(&exp, *var);
	return (tmp);
}

int		make_expansion(t_seq *tab_seq, t_list **var)
{
	t_seq	*tmp_s;
	t_list	*tmp_w;
	char	*delete;

	tmp_s = tab_seq;
	while (tmp_s)
	{
		tmp_w = tmp_s->word;
		while (tmp_w)
		{
			delete = (char *)(tmp_w->content);
			tmp_w->content = modify_str(delete, var);
			free(delete);
			if (tmp_w->content == NULL)
			{
				p_error(0, "malloc error\n", -1);
				return (-1);
			}
			tmp_w = tmp_w->next;
		}
		tmp_s = tmp_s->next_pipe;
	}
	return (0);
}
