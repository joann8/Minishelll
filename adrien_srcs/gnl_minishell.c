/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 10:30:02 by jacher            #+#    #+#             */
/*   Updated: 2021/04/08 15:40:38 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"
#include <term.h>

typedef	struct	s_term
{

	int		col;
	int		line;
	char	*name;
	char	*AF;
	char	*AB;
	char	*cl; // delete text
	char	*cm; // bouge curseur
	char	*md; // texte gras
	char	*mb; //texte clignotant
	char	*us;
	char	*me;
}				t_term;


void	ft_print_prompt(t_term *term);

void	ft_init_term_struct(t_term *term);

int		ft_termcap_on(int c)
{
	return (write(1, &c, 1));
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
	printf("Init success. Terminal name = %s\n", term->name);
	return (0);
}

void	ft_print_term(t_term *term)
{
	printf("term->col = %d\n", term->col);
	printf("term->line = %d\n", term->line);
	printf("term->af = %s\n", term->AF);
	printf("term->ab = %s\n", term->AB);

}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_term	term;
	char	*line;
	//Initialise la librairie termcap avec la var $TERM
	if (ft_init_termcap(&term))
		return (printf("termcap init failed\n"));
	ft_print_term(&term);
	while (get_next_line(0, &line))
	{
		ft_print_prompt(&term);
		ft_putstr(line);
		ft_putchar('\n');
		free(line);
	}
	free(line);
	return (0);
}


void	ft_print_prompt(t_term *term)
{
	char *prompt;

	prompt = "adrien_cpt:minishell_says$";
	tputs(term->md, 1, ft_termcap_on);
	tputs(term->us, 1, ft_termcap_on);
	tputs(tparm(term->AF, COLOR_RED), 1, ft_termcap_on);
	ft_putstr(prompt);
	tputs(term->me, 1, ft_termcap_on);
	ft_putchar(' ');
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
}


//struct termios raw;
	//char	*line;

	/*
	enable_raw_mode(&raw);
	line = gnl_minishell(&res);
	disable_raw_mode(&origin);
	printf("\n***main***\nstr:\n|%s|\nres: %d\n", line, res);
	*/

/*
void	enable_raw_mode(struct termios *origin)
{
	struct termios *raw;

	raw = origin;
	tcgetattr(STDIN_FILENO, raw);
	raw->c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, raw);
}

void	disable_raw_mode(struct termios *origin)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, origin);
}

char *gnl_minishell(int *res)
{
	char	buf[5];
	char	*line;
	int		count;
	int		bytes;
//	struct termios origin;

	line = malloc(sizeof(char) * 1); // alloue l'espace pour le end of str
	if (line == NULL) 
	{
		*res = -1; //erreur malloc
		return (NULL);
	}
	count = 0;
	line[0] = '\0';
	while ((bytes = read(0, buf, 4)) > 0)
	{
		buf[bytes] = '\0';
		printf("\ncount = %d | buf = %d \n", count, buf);
		if (buf[0] == '\n')
			break;
		else if (ft_isprint(*buf) == 1)
		{
			write(1, &buf, 1);
			line = realloc(line, sizeof(char) * (count + 2));
			if (line == NULL)
			{
				*res = -1;
				return (NULL);
			}
			line[count] = buf;
			line[count + 1] = '\0';
			count ++;
		}
	}
	*res = 0;
	return (line);
}
*/



