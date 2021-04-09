/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:31:53 by jacher            #+#    #+#             */
/*   Updated: 2021/04/09 20:46:16 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

/*
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
	if (str[*i] =='$')
	{
		*i += 1;
		*j += 1;
	}
}*/

char	*find_variable_str(char *str, int start, int end, t_list *var)
{
	t_var	*var_tmp;
	t_list	*tmp;
	char	*tofind;
	char	*toreturn;
	int		i;

	tofind = malloc(sizeof(start - end + 1));
	if (tofind == NULL)
		return (NULL);
	i = 0;
	//ft_strcpy(tofind, start + i, start - end + 1);
	while (start + i <= end)
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
			toreturn = ft_strdup(var_tmp->value);
			return (toreturn);
		}
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

char	*manage_variable2(char *str, int *i, t_list *var)
{
	char	*var_str;
	int		k;

	k = *i + 1;
	while (is_var_name(str[k]) == 1)
		k++;
	var_str = find_variable_str(str, *i + 1, k - 1, var);
	if (var_str == NULL)
		return (NULL); // erreur malloc
	*i = k;
	return (var_str);
}

char	*assign_final_str(char *tmp, char *str, t_list *var, int quote)
{
	int		i;
	int		j;
	int		l;
	char	*var_str;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			manage_quotes(str[i], &i, &j, &quote);
		else if (str[i] == '\\')
		{
			if (quote == 34)
				escape_within_doubles(str, &i);
			else if (quote == 0)
				i++;
			else if (quote == 39)
			{
				tmp[j] = str[i];
				i++;
				j++;
			}
			if (str[i] == '$')
			{
				tmp[j] = str[i];
				i++;
				j++;
			}
		}
		else if (str[i] == '$' && (quote == 0 || quote == 34))
		{
			var_str = manage_variable2(str, &i, var);
			l = 0;
			while (var_str[l])
			{
				tmp[j] = var_str[l];
				j++;
				l++;
			}
		}
		else if ((str[i] == 34 || str[i] == 39) && str[i + 1] == '\0')
			break ;
		else
		{
			tmp[j] = str[i];
			j++;
			i++;
		}
	}
	return (tmp);
}
