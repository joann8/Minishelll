/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_ft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:47:43 by jacher            #+#    #+#             */
/*   Updated: 2021/04/07 15:10:34 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	unget_char(t_source *src)
{
	if (src->curpos < 0)
		return;
	src->curpos--;
}

char	next_char(t_source *src)
{
	char c;

	if (!src || !src->buffer)
	{
		errno = ENODATA;// ??
		return (0); //ERCHAR
	}
	c = 0;
	if (src->curpos == -2) //INIT_SRC_POS
		src->curpos = -1;
	else
		c = src->buffer[src->curpos];
	src++;
	if (src->curpos >= srcs->bufsize)
	{
		src->curpos = srcs->bufsize;
		return (-1);//EOF
	}
	return (src->buffer[src->curpos]);
}

char	peek_char(t_source *src)
{
	long	pos;

	if (!src || !src->buffer)
	{
		errno = ENODATA;// ??
		return (0);//ERRRCHAR
	}
	pos = src->curpos;
	if (pos == -2)
		pos++;
	pos++;
	if (pos >= src->bufsize)
		return (-1);//EOF
	return (src->buffer[pos]);
}

void	skip_white_spaces(t_source *src)
{
	char c;

	if (!src || !src->buffer)
		return;
	c = peek_char(src);
	while (c != -1 && is_whitespace(c) > 0)
		next_char(src);
}
	

		


