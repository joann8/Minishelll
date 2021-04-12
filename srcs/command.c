/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:42:47 by jacher            #+#    #+#             */
/*   Updated: 2021/04/12 10:14:16 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int		assign_list_word(t_seq *seq, t_simple_cmd *cmd)
{
	int		i;
	t_list	*tmp;
	int		size_arg;
	
	size_arg = ft_lstsize(seq->word) - 1;
	if (size_arg > 0)
	{
		cmd->av = malloc(sizeof(char*) * size);
		if (cmd->av == NULL)
			return (-1); //erreur malloc
	}
	else
		cmd->av = NULL;
	tmp = seq->word;
	i = -1;
	while (tmp)
	{
		if (i == -1)
		{
			cmd->job = ft_strdup(tmp->content);	
			if (cmd->job == NULL)
				return (-1); //erreur malloc
		}
		else
		{
			cmd->av[i] = ft_strdup(tmp->content);
			if (cmd->job == NULL) //erreur malloc
				return (-1);

		}
		tmp = tmp->next;
		i++;
	}
	return (0);
}

t_list *create_command(t_list *cmd_list, t_seq *tab_seq, int seq_nb)
{
	int		i;
	int		j;
	t_seq	*tmp_s;
	t_list	*tmp_l;
	t_simple_cmd	*tmp_c;

	i = 0;
	j = 0;
	while (i < seq_nb)
	{
		tmp_s = &tab_seq[i];
		while (tmp_s)
		{
			tmp_c = malloc(sizeof(t_simple_cmd));
			if (tmp_c == NULL)
				return (NULL);
			if (assign_list_word(tmp_s, cmd_list->content) == -1)
				return (NULL); //erreur malloc
			if (assign_list_redir(tmp_s, cmd_list->content) == -1)
				return (NULL); //erreur malloc
			tmp_s = tmp_s->next_pipe;
			tmp_l = cmd_list;
		}
		i++;
	}



	return (cmd_list):
}
