/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_assign.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:05:44 by jacher            #+#    #+#             */
/*   Updated: 2021/04/09 12:06:47 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		assign_type_2_help(t_list **head, t_list **tmp,
			t_token *t2, t_token *t3)
{
	if (t2->e_type == SEPARATOR)
	{
		if (*tmp == *head || (t3 != NULL && (t3->e_type == PIPE ||
			t3->e_type == SEPARATOR)))
			return (-1); //print_error(int errno, char **error);
	}
	else if (t2->e_type == OUT || t2->e_type == IN || t2->e_type == APPEND)
	{
		if ((*tmp)->next == NULL || t3 == NULL || t3->e_type != WORD)
			return (-1);//print_error(int errno, char **error);
		(*tmp) = (*tmp)->next;
		((t_token *)((*tmp)->content))->e_type = FILENAME;
	}
	else if (t2->e_type == PIPE)
		if (*tmp == *head || (*tmp)->next == NULL || t3 == NULL ||
			t3->e_type == PIPE || t3->e_type == SEPARATOR)
			return (-1);//print_error(int errno, char **error);
	return (0);
}

int		assign_type_2(t_list *head)
{
	t_list	*tmp;
	t_token	*t2;
	t_token	*t3;

	tmp = head;
	while (tmp)
	{
		t2 = (t_token *)(tmp->content);
		t3 = NULL;
		if (tmp->next)
			t3 = (t_token *)(tmp->next->content);
		if (assign_type_2_help(&head, &tmp, t2, t3) == -1)
			return (-1);//print_error(int errno, char **error);
		tmp = tmp->next;
	}
	return (0);
}

void	assign_type_1(t_list *token_list)
{
	t_list	*tmp;
	t_token *tmp2;

	tmp = token_list;
	while (tmp)
	{
		tmp2 = (t_token *)tmp->content;
		if (ft_strncmp(tmp2->tok_str, "|", 2) == 0)
			tmp2->e_type = PIPE;
		else if (ft_strncmp(tmp2->tok_str, ";", 2) == 0)
			tmp2->e_type = SEPARATOR;
		else if (ft_strncmp(tmp2->tok_str, ">", 2) == 0)
			tmp2->e_type = OUT;
		else if (ft_strncmp(tmp2->tok_str, "<", 2) == 0)
			tmp2->e_type = IN;
		else if (ft_strncmp(tmp2->tok_str, ">>", 3) == 0)
			tmp2->e_type = APPEND;
		else
			tmp2->e_type = WORD;
		tmp = tmp->next;
	}
}
