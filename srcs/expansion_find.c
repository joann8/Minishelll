/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_find.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:31:53 by jacher            #+#    #+#             */
/*   Updated: 2021/04/10 11:43:29 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	ft_copy_loc(char *tofind, char *str, int start, int end)
{
	int i;

	i = 0;
	while (start + i <= end)//strncpy
	{
		tofind[i] = str[start + i];
		i++;
	}
	tofind[i] = '\0';
}

int		find_variable_length(char *str, int start, int end, t_list *var)
{
	t_var	*var_tmp;
	t_list	*tmp;
	char	*tofind;

	tofind = malloc(sizeof(start - end + 1));
	if (tofind == NULL)
		return (-1);
	ft_copy_loc(tofind, str, start, end);
//	ft_strncpy(tofind, str + start, (size_t)( start - end ));
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

int		count_final_str(t_expansion *e, t_list *var)
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
				return (-1);//erreur malloc
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

char	*find_variable_str(char *str, int start, int end, t_list *var)
{
	t_var	*var_tmp;
	t_list	*tmp;
	char	*tofind;
	char	*toreturn;

	tofind = malloc(sizeof(start - end + 1));
	if (tofind == NULL)
		return (NULL);
	ft_copy_loc(tofind, str, start, end);
	//ft_strcpy(tofind, start + i, start - end + 1);
	tmp = var;
	while (tmp)
	{
		var_tmp = (t_var *)(tmp->content);
		if (ft_strcmp(tofind, var_tmp->name) == 0)
		{
			toreturn = ft_strdup(var_tmp->value);
			return (toreturn);
		}
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

char	*assign_final_str(t_expansion *e, t_list *var)
{
	e->i = 0;
	e->j = 0;
	e->mod = 2;
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
	return (e->tmp);
}
