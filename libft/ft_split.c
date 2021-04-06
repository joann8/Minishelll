/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 11:27:39 by jacher            #+#    #+#             */
/*   Updated: 2020/11/23 19:13:40 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	unsigned int	ft_count_words(char const *s, char c)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static	void			ft_free_split(char **tab, unsigned int k)
{
	unsigned int	i;

	i = 0;
	while (i < k)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return ;
}

static	int				ft_word_size(char **tab, char const *s,
										char c, unsigned int *k)
{
	int w_size;
	int i;
	int j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			w_size = i;
			while (s[i] != c && s[i])
				i++;
			if (!(tab[j] = malloc(sizeof(char) * (i - w_size + 1))))
			{
				*k = j;
				return (0);
			}
			j++;
		}
	}
	return (-1);
}

static	void			ft_strcpy(char **tab, char const *str, char c)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	while (str[i])
	{
		k = 0;
		if (str[i] == c)
			i++;
		else
		{
			while (str[i] != c && str[i])
			{
				tab[j][k] = str[i];
				i++;
				k++;
			}
			tab[j][k] = '\0';
			j++;
		}
	}
}

char					**ft_split(char const *s, char c)
{
	char			**tab;
	unsigned int	word_count;
	unsigned int	k;

	if (!s)
		return (NULL);
	word_count = ft_count_words(s, c);
	if (!(tab = malloc(sizeof(char*) * (word_count + 1))))
		return (NULL);
	k = 0;
	if (ft_word_size(tab, s, c, &k) == 0)
	{
		ft_free_split(tab, k);
		return (NULL);
	}
	ft_strcpy(tab, s, c);
	tab[word_count] = NULL;
	return (tab);
}
