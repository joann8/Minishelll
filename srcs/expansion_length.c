/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_length.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:31:53 by jacher            #+#    #+#             */
/*   Updated: 2021/04/09 20:30:04 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	manage_quotes(char c, int *i, int *j, int *quote)
{
	if (c == 34)
	{
		if (*quote == 34)
			*quote = 0;
		else if (*quote == 0)
			*quote = 34;
		else if (*quote == 39)
			*j += 1;
	}
	else if (c == 39)
	{
		if (*quote == 39)
			*quote = 0;
		else if (*quote == 0)
			*quote = 39;
		else if (*quote == 34)
			*j += 1;
	}
	*i += 1;
}

void	manage_escape(char *str, int *i, int *j, int quote)
{
	if (quote == 34)
		escape_within_doubles(str, i);
	else if (quote == 0)
		*i += 1;
	else if (quote == 39)
	{
		*i += 1;
		*j += 1;
	}
	if (str[*i] == '$')
	{
		*i += 1;
		*j += 1;
	}
}

int		find_variable_length(char *str, int start, int end, t_list *var)
{
	t_var	*var_tmp;
	t_list	*tmp;
	char	*tofind;
	int		i;

	tofind = malloc(sizeof(start - end + 1));
	if (tofind == NULL)
		return (-1);
	i = 0;
	//ft_strncpy(tofind, (str + start), start - end + 1);
	while (start + i <= end)//strncpy
	{
		tofind[i] = str[start + i];
		i++;
	}
	tofind[i] = '\0';
	//
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

int		manage_variable(char *str, int *i, int *j, t_list *var)
{
	int k;
	int res;

	k = *i + 1;
	while (is_var_name(str[k]) == 1)
		k++;
	res = find_variable_length(str, *i + 1, k - 1, var);
	if (res == -1)
		return (-1); //erreur malloc
	*j += res;
	*i = k;
	return (0);
}

int		count_final_str(char *str, t_list *var, int quote)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			manage_quotes(str[i], &i, &j, &quote);
		else if (str[i] == '\\')
			manage_escape(str, &i, &j, quote);
		else if (str[i] == '$' && (quote == 0 || quote == 34))
		{
			if (manage_variable(str, &i, &j, var) == -1)
				return (-1); //erreur malloc
		}
		else if ((str[i] == 34 || str[i] == 39) && str[i + 1] == '\0')
			break ;
		else
		{
			j++;
			i++;
		}
	}
	return (j);
}
