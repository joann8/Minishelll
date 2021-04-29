/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_main_words.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:42:47 by jacher            #+#    #+#             */
/*   Updated: 2021/04/29 13:33:57 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void 	calculate_size_trim(char *new, int *word, int *count)
{
	int		i;
	int		mod;
	int		to_add;
	
	i = 0;
	mod = 0;
	to_add = 0;
	while (new[i])
	{
		if (new[i] != ' ')
		{
			to_add++;
			if (mod == 0)
				mod = 1;
		}
		else
		{
			if (to_add != 0)
				*word +=1;
			*count += to_add;
			to_add = 0;
		}
		i++;
	}
	if (to_add != 0)
		*word +=1;
	*count += to_add;
}

char	*trim_spaces_for_echo(char *new)
{
	int		word;
	int		count;
	int		i;
	int		j;
	char	*tmp;
	int		mod;

	word = 0;
	count = 0;
	calculate_size_trim(new, &word, &count);
	if ((tmp = malloc(sizeof(char) * (count + word))) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	mod = 0;
	while (new[i])
	{
		if (new[i] != ' ')
		{
			tmp[j] = new[i];
			j++;
			mod = 1;
		}
		else if (new[i] == ' ' && mod == 1 && j < count + word - 1)
		{
			tmp[j] = ' ';
			j++;
			mod = 0;
		}
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

int			check_quote_for_echo(char *str)
{
	int quote;
	int i;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			if (quote == 0)
				quote = 34;
			else if (quote == 34)
				quote = 0;
		}
		else if (str[i] == '$' && quote == 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int			assign_list_word(t_seq *seq, t_simple_cmd *cmd, t_list **env)
{
	int		i;
	char	*new;
	t_list	*tmp;

	tmp = seq->word;
	i = 0;
	while (tmp)
	{
		if (tmp->content)
		{
			if (i == 0)
			{
				cmd->job = ft_strdup((char *)tmp->content);
				if (cmd->job == NULL)
					return (p_error(0, "malloc error\n", -1));
			}
			new = modify_str((char*)tmp->content, env);
			if (new == NULL)//erreur malloc // pas  besoin de free(cmd->job) je crois car free en sortant
				return (p_error(0, "malloc error\n", -1));
			if (i > 0 && (ft_strcmp(cmd->av[0], "export") == 0) 
				&& (ft_strcmp(tmp->content, "\"\"") != 0)
				&& ft_strcmp(new, "") == 0)
			{
				cmd->av[i] = NULL;
				free(new);
			}
			else if (i > 0 && ft_strcmp(cmd->av[0], "echo") == 0
				&& check_quote_for_echo((char*)tmp->content) == 1) 
			{
				cmd->av[i] = trim_spaces_for_echo(new);
				free(new);
				if (cmd->av[i] == NULL)
					return (p_error(0, "malloc error\n", -1));
			}
			else
				cmd->av[i] = new;
		}
		tmp = tmp->next;
		i++;
	}
	cmd->av[i] = NULL;
	return (0);
}
