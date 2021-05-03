/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_main_words.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:42:47 by jacher            #+#    #+#             */
/*   Updated: 2021/05/03 18:02:03 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void		calculate_size_trim(char *new, int *word, int *count, int mod)
{
	int		i;
	int		to_add;

	i = 0;
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
				*word += 1;
			*count += to_add;
			to_add = 0;
		}
		i++;
	}
	if (to_add != 0)
		*word += 1;
	*count += to_add;
}

char		*trim_spaces_for_echo(char *new, int i, int j, int mod)
{
	int		w;
	int		c;
	char	*tmp;

	w = 0;
	c = 0;
	calculate_size_trim(new, &w, &c, 0);
	if ((tmp = malloc(sizeof(char) * (c + w))) == NULL)
		return (NULL);
	while (new[i])
	{
		if (new[i] != ' ' || (new[i] == ' ' && mod == 1 && j < c + w - 1))
		{
			tmp[j] = new[i];
			j++;
			if (new[i] != ' ')
				mod = 1;
			else
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
		if (str[i] == '\\')
			i++;
		if (str[i] == '"')
		{
			if (quote == 0)
				quote = 34;
			else if (quote == 34)
				quote = 0;
			i++;
		}
		else if (str[i] == '$' && quote == 0)
			return (1);
		else
			i++;
	}
	return (0);
}

int			assign_cmd_av(t_simple_cmd *cmd, t_list *tmp, char *new, int i)
{
	if (i > 0 
		&& (ft_strcmp(cmd->av[0], "export") == 0 
		|| ft_strcmp(cmd->av[0], "unset") == 0)
		&& (ft_strcmp(tmp->content, "\"\"") != 0)
		&& ft_strcmp(new, "") == 0)
	{
		cmd->av[i] = NULL;
		free(new);
	}
	else if (i > 0 && ft_strcmp(cmd->av[0], "echo") == 0)
	{
		if (ft_strcmp(new, "") != 0)	
		{
			if (check_quote_for_echo((char*)tmp->content) == 1)
			{
				cmd->av[i] = trim_spaces_for_echo(new, 0, 0, 0);
				free(new);
				if (cmd->av[i] == NULL)
					return (p_error(0, "malloc error\n", -1));
			}
			else
				cmd->av[i] = new;
		}
		else if (ft_strcmp((char*)tmp->content, "\"\"") == 0
					|| check_quote_for_echo((char*)tmp->content) == 0)
			cmd->av[i] = new;
		else
		{
			cmd->av[i] = NULL;
			free(new);
		}
	}
	else
		cmd->av[i] = new;
	printf("(AD)cmd->av[%d] = %s\n", i, cmd->av[i]);
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
				if ((cmd->job = ft_strdup((char *)tmp->content)) == NULL)
					return (p_error(0, "malloc error\n", -1));
			if ((new = modify_str((char*)tmp->content, env)) == NULL)//erreur malloc // pas  besoin de free(cmd->job) je crois car free en sortant
				return (p_error(0, "malloc error\n", -1));
			if (assign_cmd_av(cmd, tmp, new, i) == -1)
				return (-1);
		}
		tmp = tmp->next;
		i++;
	}
	cmd->av[i] = NULL;
	return (0);
}
