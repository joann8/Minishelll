/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:31:53 by jacher            #+#    #+#             */
/*   Updated: 2021/04/09 15:39:16 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	escape_within_doubles(char *str, int *pos)
{
	int i;

	i = *pos + 1;
	if (str[i] == '$' || str[i] == 34 || str[i] == 39 || str[i] == '\\')
		*pos += 1;
	//special character also : ! 
}

int		find_variable_length(char *str, int start, int end, t_list *var)
{
	t_var	*var_tmp;
	t_list	*tmp;
	char 	*tofind;

	tofind = malloc(sizeof(start - end + 1));
	if (tofind == NULL)
		return (-1);
	i = 0;
	while (start + i <= end)
	{
		tofind[i] = str[start + i];
		i++;
	}
	tofind[i] = '\0';
	tmp = var;
	while (tmp)
	{
		var_tmp = (t_var *)(tmp->content);
		if (ft_strncmp(tofind, var_tmp->name, ft_strlen(tofind)) == 0)
			return (ft_strlen(var_tmp->value));
		tmp->tmp->next;
	}
	return (-1);
}

int		count_final_str(char *str, t_list *var, int quote)
{
	int		i;
	int		j;
	int		k;
	int 	res;

	i = 0;
	j = 0;
	if (quote == 39 || quote == 34)
		i++;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			if (quote == 34)	
				escape_within_doubles(str, &i);
			if (quote == 0)	
				i++;
		}
		else if (str[i] == '$' && (quote == 0 || quote == 39))
		{
			//on a trouvé une vraie variable dont on doit afficher le nom	
			k = i + 1;
			while (is_whitespace(str[k]) == 0)
				k++;
			res = find_variable_length(str, i + 1, k - 1, var);
			if (res == -1)
				return (-1); // erreur variable non trouvée
			j += res - 1;//-1 car j++ a la fin
			i = k - 1;;//-1 car i++ a la fin
		}
		else if ((str[i] == 34 || str[i] == 39) && str[i + 1] =='\0')
			break;
		j++;
		i++;
	}
	printf("j = %d\n", j);
	return(j);
}

char *find_variable_str(char *str, int start, int end, t_list *var)
{
	t_var	*var_tmp;
	t_list	*tmp;
	char 	*tofind;
	char	*toreturn;

	tofind = malloc(sizeof(start - end + 1));
	if (tofind == NULL)
		return (NULL);
	i = 0;
	while (start + i <= end)
	{
		tofind[i] = str[start + i];
		i++;
	}
	tofind[i] = '\0';
	tmp = var;
	while (tmp)
	{
		var_tmp = (t_var *)(tmp->content);
		if (ft_strncmp(tofind, var_tmp->name, ft_strlen(tofind)) == 0)
		{
			toreturn = ft_strncpy(var_tmp->value, ft_strlen(var_tmp->value));
			return (toreturn);
		}
		tmp->tmp->next;
	}
	return (NULL);
}

char	*assign_final_str(char *tmp, char *str, t_list *var, int quote)
{
	int		i;
	int		j;
	int		k;
	int		l;
	char 	*var_str;

	i = 0;
	j = 0;
	if (quote == 39 || quote == 34)
		i++;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			if (quote == 34)	
				escape_within_doubles(str, &i);
			if (quote == 0)	
				i++;
			tmp[j] = str[i];
		}
		else if (str[i] == '$' && (quote == 0 || quote == 39))
		{
			//on a trouvé une vraie variable dont on doit afficher le nom	
			k = i + 1;
			while (is_whitespace(str[k]) == 0)
				k++;
			var_str = find_variablei_str(str, i + 1, k - 1, var);
			if (var_str == NULL)
				return (NULL); // erreur variable non trouvée
			l = 0;
			while (var_str[l])
			{
				tmp[j] = var_str[l];
				j++;
				l++;
			}
			i = k - 1;
		}
		else if ((str[i] == 34 || str[i] == 39) && str[i] == '\0')
			break;
		else
			tmp[j] = str[i];
		j++;
		i++;
	}
	return(tmp);
}

char	*modify_str(char *str, t_list *var)
{
	int		quote; //0 no - 39 simple - 34 double
	char	*tmp;
	int		size;

	quote = 0;
	if (str[0] == 39 || str[0] == 34)
		quote = (int)str[i];
	size = count_final_str(str, var, quote);
	if (size < 0)
		return (NULL);
	tmp = malloc(sizeof(char) * (size + 1));
	if (tmp == NULL)
		return (NULL);
	tmp = assign_final_str(str, var, quote);
	return (tmp);
}

tab_seq *(t_seq tab_seq, t_list token_list, int seq_nb)
{
	int		i;
	int 	j;
	t_seq	*tmp_s;
	t_list	*tmp_w;
	char	*delete;

	i = 0;
	while (i < seq_nb)
	{
		tmp_s = &tab_seq[i];
		j = 0;
		while (j <= tmp_s->pipe_total)
		{
			tmp_w = tmp_s->word;
			while (tmp_w)
			{
				delete = tmp_w->content;
				tmp_w->content = modify_str(delete, var);
				free (delete);
				if (tmp_w->content == NULL)
					return (NULL);
				tmp = tmp->next
			}
			j++;
		}
		i++;
	}
	return(tab_seq);
}
