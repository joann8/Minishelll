/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_userinput.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 10:30:02 by jacher            #+#    #+#             */
/*   Updated: 2021/04/09 20:21:41 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int	ft_get_userinput(char **line, t_list *log)
{
	t_term			term;
	struct termios	origin;
	unsigned int				log_size;

	log_size = ft_lstsize(log);
	printf("log_size = %d\n", log_size);
	//Initialise la librairie termcap avec la var $TERM
	ft_enable_raw_mode(&origin);
	if (ft_init_termcap(&term))
		return (-(printf("termcap init failed\n")));
	*line = ft_read_input(STDIN_FILENO, &term, log, log_size);
	if (*line == NULL)
	{
		printf("error in get_raw_input\n");
		return (-1);
	}
	tputs(term.me, 1, ft_termcap_on);
	ft_disable_raw_mode(&origin);
	return (1);
}



char	*ft_read_input(int fd, t_term *term, t_list *log, unsigned int log_size)
{
	char				buf[5];
	int					bytes;
	char				*screen;
	char				*user_input;
	char				*to_free;
	unsigned	int		i;

	i = log_size;
	user_input = ft_strdup("");
	if (user_input == NULL)
		return (NULL);
	screen = user_input;
	ft_print_prompt(term);
	while ((bytes = read(fd, buf, 4)))
	{
		buf[bytes] = '\0';
		//Analyse la chaine buf
		if (ft_isprint(buf[0]))
		{
			to_free = screen;
			screen = ft_strjoin(screen, buf);
			free(to_free);
			if (screen == NULL)
				return (NULL);
			write(1, &screen[ft_strlen(screen)], 1);
		}
		else
		{
			//fin du user_input
			if (buf[0] == '\n')
			{
				screen[ft_strlen(screen)] = '\0';
				write(1, &screen[ft_strlen(screen)], 1);
				write(1, "\n", 1);
				return (screen);
			}
			//backspace
			else if (buf[0] == 127)
				screen[ft_strlen(screen) - 1] = '\0';
			else if (buf[0] == 27 && buf[1] == '[' 
					&& (buf[2] == 'B' || buf[2] == 'A'))	
			{
				// A == UP
				if (buf[2] == 'A')
				{
					printf("\nUP_ARROW hooked\n");
					if (i > 0)
						i--;
					screen = (char *)((ft_lstat(log, i))->content);
				}
				// B == DOWN
				else if (buf[2] == 'B')
				{
					printf("\nDOWN_ARROW hooked\n");
					if (i < log_size - 1)
					{
						i++;
						screen = (char *)((ft_lstat(log, i))->content);
					}
					else
					{
						printf("user_input = %s\n", user_input);
						screen = user_input;
						if (i < log_size)
							i++;
					}

				}
			}
			else
				printf("\nSPECIAL_CHAR hooked.SO WHAT..?\n");
		}
		printf("i = %d\n", i);
		//efface l'input du 
		tputs(term->cb, 1, ft_termcap_on);
		//remet le curseur en debut de ligne
		tputs(tparm(term->ch, 0), 1, ft_termcap_on);
		//imprime le prompt sur le stdout
		ft_print_prompt(term);
		//Imprime la ligne sur le stdout
		write(1, screen, ft_strlen(screen));
	}
	return (NULL);
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
	return (0);
}

void	ft_print_prompt(t_term *term)
{
	char *prompt;

	prompt = "Minishell_says$";
	//Mets le prompt en gras
	tputs(term->md, 1, ft_termcap_on);
	//Souligne le prompt
	tputs(term->us, 1, ft_termcap_on);
	//Choisir la couleur du prompt
	tputs(tparm(term->AF, COLOR_BLUE), 1, ft_termcap_on);
	ft_putstr(prompt);
	//Reset les settings d'ecriture
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
	term->cb = tgetstr("cb", NULL);
	term->ch = tgetstr("ch", NULL);
}

