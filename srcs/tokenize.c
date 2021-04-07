/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:05:44 by jacher            #+#    #+#             */
/*   Updated: 2021/04/07 20:18:50 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		assign_type_2(t_list *head)
{
	t_list	*tmp;
	t_token	*t2;
	t_token	*t3;

	tmp = head;
	while (tmp)
	{
		t2 = (t_token *)tmp->content;
		t3 = NULL;
		if (tmp->next)
			t3 = (t_token *)tmp->next->content;
		if (t2->e_type == SEPARATOR)
		{
			if (tmp == head || t3->e_type == PIPE || t3->e_type == SEPARATOR)
				return (-1); //print_error(int errno, char **error);
		}
		else if (t2->e_type == OUT || t2->e_type == IN || t2->e_type == APPEND)
		{
			if (tmp->next == NULL || t3->e_type != WORD)
				return (-1);//print_error(int errno, char **error);
			tmp = tmp->next;
			((t_token *)(tmp->content))->e_type = FILENAME;
		}
		else if (t2->e_type == PIPE)
			if (tmp == head || tmp->next == NULL || t3->e_type == PIPE
				|| t3->e_type == SEPARATOR)
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

int		ft_create_token(t_list **token_list, char *input, int start, int end)
{
	t_token	*token;

	token = malloc(sizeof(token));
	if (token == NULL)
		return (-1); //erreur malloc//print_error(int errno, char **error);
	token->tok_str = malloc(sizeof(char) * (end - start + 2));
	if (token->tok_str == NULL)
		return (-1); //erreur malloc//print_error(int errno, char **error);
	ft_strlcpy(token->tok_str, input + start, end - start + 2);
	ft_lstadd_back(token_list, ft_lstnew((void *)token));
	return (0);
}

t_list	*ft_get_token_list(t_list *token_list, char *inp)
{
	int		i;
	int		start;

	i = 0;
	while (inp[i])
	{
		while (inp[i] && is_whitespace(inp[i]) > 0)
			i++;
		start = i;
		if (is_spec(inp[i], '|') == 1 || is_spec(inp[i], ';') == 1
			|| is_spec(inp[i], '>') == 1)
		{
			i++;
			if (is_spec(inp[i], '>') == 1)
				i++;
		}
		else
		{
			while (inp[i] && is_whitespace(inp[i]) == 0)
			{
				if (is_spec(inp[i], '|') == 1 || is_spec(inp[i], ';') == 1
					|| is_spec(inp[i], '<') == 1 || is_spec(inp[i], '>') == 1)
					break ;
				if (is_spec(inp[i], 34) == 1)
					if (look_second_quote(34, inp, &i) == -1)
						return (NULL); // erreur quote pas fermée;//print_error(int errno, char **error);
				if (is_spec(inp[i], 39) == 1)
					if (look_second_quote(39, inp, &i) == -1)
						return (NULL); // erreur quote pas fermée;//print_error(int errno, char **error);
				i++;
			}
		}
		if (i != start)
			if (ft_create_token(&token_list, inp, start, i - 1) == -1)
				return (NULL); //erreur malloc//print_error(int errno, char **error);
	}
	return (token_list);
}
