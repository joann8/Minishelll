/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:58:48 by calao             #+#    #+#             */
/*   Updated: 2021/04/20 14:34:36 by calao            ###   ########.fr       */
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
		return (-1);
	}
	ret = tgetent(NULL, term->name);
	if (ret == 0)
	{
		printf("tgetent == 0\n");
		return (-1);
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

int		ft_is_endofscreen(t_term *term, char *prompt)
{
	int		cur_row;
	int		cur_col;

	if (ft_getcursorxy(&cur_row, &cur_col))
	{
		printf("Error while reading cursors position\n");
		return (-1);
	}
	if (cur_row == term->line && cur_col == term->col)
		ft_move_cursor_home(term, prompt);
	return (0);
}



void	ft_move_cursor_home(t_term *term, char *prompt)
{
	tputs(tgoto(term->cm, 0, 0), 1, ft_termcap_on);
	tputs(term->cd, 1, ft_termcap_on);
	ft_print_prompt(term, prompt);
	tputs(term->sc, 1, ft_termcap_on);
}

int		ft_getcursorxy(int *row, int *col)
{
	char	buf[1000];
	int		bol;
	int		i;
	int		ret;


	write(STDOUT_FILENO, "\033[6n", 4);
	ret = read(STDIN_FILENO, &buf, 1000);
	if (ret <= 0)
		return (-1);
	buf[ret] = '\0';
	i = 0;
	bol = 0;
	while (buf[i] && buf[i] != '[')
		i++;
	while (buf[i])
	{
		if (ft_isdigit(buf[i]))
		{
			if (bol == 0)
			{
				*row = ft_atoi(buf + i);
				bol = 1;
				while (ft_isdigit(buf[i]))
						i++;
			}
			else
			{
				*col = ft_atoi(buf +i);
				return (0);
			}
		}
		i++;
	}
	return (0);
}


