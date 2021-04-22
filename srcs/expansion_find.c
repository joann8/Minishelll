/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_find.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:31:53 by jacher            #+#    #+#             */
/*   Updated: 2021/04/22 18:58:47 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int			find_variable_length(char *str, int start, int end, t_list *var)
{
	t_var	*var_tmp;
	t_list	*tmp;
	char	*tofind;

	tofind = malloc(sizeof(char) * (end - start + 2));
	if (tofind == NULL)
		return (p_error(0, "malloc erroc\n", -1));
	ft_copy_loc_expansion(tofind, str, start, end);
	tmp = var;
	while (tmp)
	{
		var_tmp = (t_var *)(tmp->content);
		if (ft_strcmp(tofind, var_tmp->name) == 0)
		{
			free(tofind);
			return (ft_strlen(var_tmp->value));
		}
		tmp = tmp->next;
	}
	free(tofind);
	return (0);
}

int			count_final_str(t_expansion *e, t_list *var)
{
	e->i = 0;
	e->j = 0;
	e->mod = 1;
	e->quote = 0;
	while (e->str[e->i])
	{
		if (e->str[e->i] == 34 || e->str[e->i] == 39)
			manage_quotes(e, e->str[e->i]);
		else if (e->str[e->i] == '\\')
			manage_escape(e);
		else if (e->str[e->i] == '$' && (e->quote == 0 || e->quote == 34))
		{
			if (manage_variable(e, var) == -1)
				return (-1);
		}
		else if ((e->str[e->i] == 34 || e->str[e->i] == 39)
					&& e->str[e->i + 1] == '\0')
			break ;
		else
		{
			e->j += 1;
			e->i += 1;
		}
	}
	return (e->j);
}

char		*find_variable_str(char *str, int start, int end, t_list *var)
{
	t_var	*var_tmp;
	t_list	*tmp;
	char	*tofind;
	char	*toreturn;

	toreturn = NULL;
	tofind = malloc(sizeof(char) * (end - start + 2));
	if (tofind == NULL)
		return (NULL);
	ft_copy_loc_expansion(tofind, str, start, end);
	tmp = var;
	while (tmp)
	{
		var_tmp = (t_var *)(tmp->content);
		if (ft_strcmp(tofind, var_tmp->name) == 0)
		{
			//toreturn = ft_strdup(var_tmp->value);//JE COMPRENDS PAS LA LEAK
			toreturn = var_tmp->value;
			free(tofind);
			return (toreturn);
		}
		tmp = tmp->next;
	}
	free(tofind);
	return (ft_strdup(""));
}

static void	init_expansion(t_expansion *e)
{
	e->i = 0;
	e->j = 0;
	e->mod = 2;
	e->quote = 0;
}

char		*assign_final_str(t_expansion *e, t_list *var)
{
	init_expansion(e);
	while (e->str[e->i])
	{
		if (e->str[e->i] == 34 || e->str[e->i] == 39)
			manage_quotes(e, e->str[e->i]);
		else if (e->str[e->i] == '\\')
			manage_escape(e);
		else if (e->str[e->i] == '$' && (e->quote == 0 || e->quote == 34))
		{
			if (manage_variable(e, var) == -1)
				return (NULL);
		}
		else if ((e->str[e->i] == 34 || e->str[e->i] == 39)
					&& e->str[e->i + 1] == '\0')
			break ;
		else
		{
			e->tmp[e->j] = e->str[e->i];
			e->j += 1;
			e->i += 1;
		}
	}
	e->tmp[e->j] = '\0';
	return (e->tmp);
}
