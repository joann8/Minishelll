/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:42:47 by jacher            #+#    #+#             */
/*   Updated: 2021/04/12 12:51:25 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		assign_list_redir(int pipe[2], t_seq *seq, t_simple_cmd *cmd)
{
	t_list	*tmp;
	int		size_arg;


	size_arg = ft_lstsize(seq->redir);
	tmp = seq->redir;
	while (tmp)
	{
		if (tmp->e_type == IN)

		else if (tmp->e_type == OUT)

		else if (tmp->e_type == APPEND)
		i++;
	}
	return (0);

}

int		assign_list_word(t_seq *seq, t_simple_cmd *cmd)
{
	int		i;
	t_list	*tmp;
	int		size_arg;
	
	size_arg = ft_lstsize(seq->word) - 1;
	cmd->ac = size_arg;;
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
	int				i;
	int				j;
	t_seq			*tmp_s;
	t_list			*tmp_l;
	t_simple_cmd	*tmp_c;
	int				pipe_link;

	i = 0;
	j = 0;
	pipe_link = -1;
	while (i < seq_nb)
	{
		tmp_s = &tab_seq[i];
		std_in = 0;
		std_out = 1; 
		while (tmp_s)
		{
			tmp_c = malloc(sizeof(t_simple_cmd));
			if (tmp_c == NULL)
				return (NULL);
			if (assign_list_word(tmp_s, tmp_c) == -1)
				return (NULL); //erreur malloc
			if (assign_list_redir(pipe_link, tmp_s, tmp_c) == -1)
				return (NULL); //erreur malloc
			ft_lstadd_back(&cmd_list, ft_lstnew((void*)tmp_c);
			tmp_s = tmp_s->newt_pipe;
		}
		i++;
	}
	return (cmd_list):
}
