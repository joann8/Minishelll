/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:05:44 by jacher            #+#    #+#             */
/*   Updated: 2021/04/14 15:33:02 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		ft_create_token(t_list **token_list, char *input, int start, int end)
{
	t_token	*token;
	t_list 	*new;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (print_error(0, "malloc error\n"));
		//return (-1); //erreur malloc >> quoi afficher?
	token->tok_str = (char *)malloc(sizeof(char) * (end - start + 2));
	if (token->tok_str == NULL)
	{
		free(token);
		return (print_error(0, "malloc error\n"));
	}
		//return (-1); //erreur malloci >> quoi afficher?
	ft_strlcpy(token->tok_str, input + start, end - start + 2);
	new = ft_lstnew((void *)token);//protection malloc de ft_lst new?
	if (new == NULL)
	{
		free(token->tok_str);
		free(token);
		return (print_error(0, "malloc error\n"));
	}
	ft_lstadd_back(token_list, new);//protection malloc de ft_lst new?
	//free(new);
	return (0);
}

int		analyze_inputs(char *inp, int *pos)
{
	int i;

	i = *pos;
	while (inp[i] && !is_whitespace(inp[i]))
	{
		if (inp[i] == '|' == 1 || inp[i] == ';' || inp[i] == '<' ||
				inp[i] == '>')
			break ;
		if (inp[i] == 34)
			if (look_second_quote(34, inp, &i) == -1)
				return (print_error(0, "syntax error : quote is not closed\n"));
				//return (-1);//erreur quote pas fermée;//print_error(int errno, char **error);
		if (inp[i] == 39)
			if (look_second_quote(39, inp, &i) == -1)
				return (print_error(0, "syntax error : quote is not closed\n"));
				//return (-1);//erreur quote pas fermée;//print_error(int errno, char **error);
		if (inp[i] == '\\')
			escape_quote(inp, &i);
		i++;
	}
	*pos = i;
	return (0);
}

int		ft_get_token_list(t_list **token_list, char *s)
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
				return (-1); //erreur manage dans analyze inputs
		}
		if (i != start)
			if (ft_create_token(token_list, s, start, i - 1) == -1)
				return (-1); ///erreur manage dans create token
	}
	return (0);
}
