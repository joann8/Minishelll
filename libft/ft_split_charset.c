/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 15:04:18 by louise            #+#    #+#             */
/*   Updated: 2020/09/28 15:06:13 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_nb_words(char *str, char *charset)
{
	int		nb_words;
	char	p_char;
	int		i;

	nb_words = 0;
	p_char = -1;
	i = 0;
	while (str[i])
	{
		if ((p_char == -1 || is_charset(p_char, charset))
			&& !is_charset(str[i], charset))
			nb_words++;
		p_char = str[i];
		i++;
	}
	return (nb_words);
}

static int	ft_word_len(char *str, char *charset)
{
	int	i;

	i = 0;
	while (str[i] && !is_charset(str[i], charset))
		i++;
	return (i);
}

static char	*set_new_word(char *str, char *charset, int word_len)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(sizeof(char) * (word_len + 1));
	if (!word)
		return (NULL);
	while (str[i] && !is_charset(str[i], charset))
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split_charset(char *str, char *charset)
{
	int		p_char;
	char	**words_tab;
	int		word_nb;
	int		word_len;

	p_char = -1;
	word_nb = 0;
	words_tab = malloc(sizeof(char*) * (ft_nb_words(str, charset) + 1));
	if (!words_tab)
		return (NULL);
	while (*str)
	{
		if ((p_char == -1 || is_charset(p_char, charset))
			&& !is_charset(*str, charset))
		{
			word_len = ft_word_len(str, charset);
			words_tab[word_nb] = set_new_word(str, charset, word_len);
			if (!words_tab[word_nb++])
				return (free_double_tab(words_tab));
		}
		p_char = *str++;
	}
	words_tab[word_nb] = NULL;
	return (words_tab);
}
