/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:31:53 by jacher            #+#    #+#             */
/*   Updated: 2021/04/09 20:32:39 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	escape_within_doubles(char *str, int *pos)
{
	int i;

	i = *pos + 1;
	if (str[i] == '$' || str[i] == 34 || str[i] == 39 || str[i] == '\\')
		*pos += 1;//special character also : !
}

char	*modify_str(char *str, t_list *var)
{
	char	*tmp;
	int		size;
	int		quote;

	quote = 0;
	size = count_final_str(str, var, quote);
	printf("size = %d\n", size);
	if (size == -1)//erreur malloc
		return (NULL);
	if (size == 0)
		return (ft_strdup(""));
	tmp = malloc(sizeof(char) * (size + 1));
	if (tmp == NULL)
		return (NULL);
	tmp = assign_final_str(tmp, str, var, quote);
	return (tmp);
}

t_seq	*make_expansion(t_seq *tab_seq, int seq_nb, t_list *var)
{
	int		i;
	t_seq	*tmp_s;
	t_list	*tmp_w;
	char	*delete;

	i = -1;
	while (++i < seq_nb)
	{
		tmp_s = &tab_seq[i];
		while (tmp_s)
		{
			tmp_w = tmp_s->word;
			while (tmp_w)
			{
				delete = (char *)tmp_w->content;
				tmp_w->content = modify_str(delete, var);
				free(delete);
				if (tmp_w->content == NULL)
					return (NULL);
				tmp_w = tmp_w->next;
			}
			tmp_s = tmp_s->next_pipe;
		}
	}
	return (tab_seq);
}
