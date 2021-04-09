/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:05:44 by jacher            #+#    #+#             */
/*   Updated: 2021/04/09 12:05:54 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

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

int		analyze_inputs(char *inp, int *pos)
{
	int i;

	i = *pos;
	while (inp[i] && !is_whitespace(inp[i]))// == 0)
	{
		if (inp[i] == '|' == 1 || inp[i] == ';' || inp[i] == '<' ||
				inp[i] == '>')
			break ;
		if (inp[i] == 34)
			if (look_second_quote(34, inp, &i) == -1)
				return (-1);//erreur quote pas fermée;//print_error(int errno, char **error);
		if (inp[i] == 39)
			if (look_second_quote(39, inp, &i) == -1)
				return (-1);//erreur quote pas fermée;//print_error(int errno, char **error);
		if (inp[i] == '\\')
			escape_quote(inp, &i);
		i++;
	}
	*pos = i;
	return (0);
}

t_list	*ft_get_token_list(t_list *token_list, char *s)
{
	int		i;
	int		start;

	i = 0;
	while (s[i])
	{
		while (s[i] && is_whitespace(s[i]))// > 0)
			i++;
		start = i;//avec la suite pour le moment <> ne fonctionne pas
		if (s[i] == '|' || s[i] == ';' || s[i] == '<' || s[i] == '>')
		{
			i++;
			if (comp(s[i - 1], '>') && comp(s[i], '>'))
				i++;
		}
		else
		{
			if (analyze_inputs(s, &i) == -1)
				return (NULL);
		}
		if (i != start)
			if (ft_create_token(&token_list, s, start, i - 1) == -1)
				return (NULL); //erreur malloc//print_error(int errno, char **error);
	}
	return (token_list);
}
