/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:31:53 by jacher            #+#    #+#             */
/*   Updated: 2021/04/27 18:27:30 by jacher           ###   ########.fr       */
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
//	printf("here!\n");
//	printf("str = %s\n", exp.str);
	size = count_final_str(&exp, *var);
	
//	printf("size = %d\n", size);
//	printf("str = %s\n", str);
	if (size == -1)
		return (NULL);
	if (size == 0)
	{
		if ((tmp = ft_strdup("")) == NULL)
			p_error(0, "malloc error\n", -1);
		return (tmp);
	}
//	printf("here!\n");
	exp.tmp = malloc(sizeof(char) * (size + 1));
	if (exp.tmp == NULL)
	{
		p_error(0, "malloc error\n", -1);
		return (NULL);
	}
	tmp = assign_final_str(&exp, *var);
	return (tmp);
}

int		make_expansion(t_seq *tab_seq, t_list **var)
{
	t_seq	*tmp_s;
	t_list	*tmp_w;
	char	*new;
	//char	*delete;

	tmp_s = tab_seq;
	while (tmp_s)
	{
		tmp_w = tmp_s->word;
		while (tmp_w)
		{
			new = modify_str(tmp_w->content, var);
			free((char*)(tmp_w->content));
			tmp_w->content = ft_strdup(new); 
			free(new);
			if (tmp_w->content == NULL)
				return (-1);
			tmp_w = tmp_w->next;
		}
		tmp_s = tmp_s->next_pipe;
	}
	return (0);
}
