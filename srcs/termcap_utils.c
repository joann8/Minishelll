/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:58:48 by calao             #+#    #+#             */
/*   Updated: 2021/04/15 15:49:26 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		ft_termcap_on(int c)
{
	return (write(1, &c, 1));
}

void	ft_enable_raw_mode(struct termios *origin)
{
	struct termios raw;

	tcgetattr(STDIN_FILENO, origin);
	raw = *origin;
	raw.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void	ft_disable_raw_mode(struct termios *origin)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, origin);
}

int		ft_init_termcap(t_term *term)
{
	int		ret;

	term->name = getenv("TERM");
	if (term->name == NULL)
	{
		printf("env '$TERM' not found\n");
		return (1);
	}
	ret = tgetent(NULL, term->name);
	if (ret == 0)
	{
		printf("tgetent == 0\n");
		return (1);
	}
	else if (ret == -1)
	{
		printf("terminfo '%s' database not found\n", term->name);
		return (-1);
	}
	ft_init_term_struct(term);
	return (0);
}


void	ft_init_term_struct(t_term *term)
{
	term->col = tgetnum("co");
	term->line = tgetnum("li");
	term->cl = tgetstr("cl", NULL);
	term->cm = tgetstr("cm", NULL);
	term->md = tgetstr("md", NULL);
	term->mb = tgetstr("mb", NULL);
	term->AF = tgetstr("AF", NULL);
	term->AB = tgetstr("AB", NULL);
	term->us = tgetstr("us", NULL);
	term->me = tgetstr("me", NULL);
	term->cb = tgetstr("cb", NULL);
	term->ch = tgetstr("ch", NULL);
	term->ce = tgetstr("ce", NULL);
	term->sc = tgetstr("sc", NULL);
	term->rc = tgetstr("rc", NULL);
	term->cd = tgetstr("cd", NULL);
}
