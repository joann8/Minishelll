/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_userinput.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 10:30:02 by jacher            #+#    #+#             */
/*   Updated: 2021/04/11 19:09:38 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

char	*ft_strndup(char *src, int len);
int		ft_isempty(char *str);
int		ft_edit_line(char **screen, char *buf, unsigned int s_len);
int		ft_update_log(char **screen, t_list *log, int fd_log);

int		ft_down_arrow(char **screen, char **user_input, 
								t_list *log, unsigned int *i);

int		ft_up_arrow(char **screen, char **user_input, 
								t_list *log, unsigned int *i);
	
	
	
	
	
typedef	struct s_input
{
	unsigned int	i;
	unsigned int	log_size;
	char			buf[5];
	char			*screen;
	char			*input;
}		t_input;

int	ft_get_userinput(int fd_log, char **line, t_list *log)
{
	t_term			term;
	struct termios	origin;

	//Initialise la librairie termcap avec la var $TERM
	ft_enable_raw_mode(&origin);
	if (ft_init_termcap(&term))
		return (-(printf("termcap init failed\n")));
	*line = ft_read_input(STDIN_FILENO, &term, log);
	tputs(term.me, 1, ft_termcap_on);
	ft_disable_raw_mode(&origin);
	if (*line == NULL)
		return (printf("error in get_raw_input\n"));
	if (ft_update_log(line, log, fd_log) == -1)
		return (-1); // Err malloc
	return (1);
}

int		ft_screen_wrapper(t_input *user, t_list *log)
{
	unsigned int	s_len;
	char			*buf;

	buf = user->buf;
	s_len = ft_strlen(user->screen);
	if (/*bytes == 1 && */(ft_isprint(buf[0]) || buf[0] == 127))
		{
			if (ft_edit_line(&(user->screen), buf, s_len) == -1)
				return (-1); // Malloc error;
		}
		//Changement de screen display
		else if (buf[0] == 27 && buf[1] == '[' && buf[2] == 'B')
		{
			if (ft_down_arrow(&(user->screen), &(user->input),
							log, &(user->i)) == -1)
					return (-1); // MALLOC ERROR
		}
		else if (buf[0] == 27 && buf[1] == '[' && buf[2] == 'A')
		{
			if (ft_up_arrow(&(user->screen), &(user->input),
						log, &(user->i)) == -1)
					return (-1); // Err malloc
		}
		//else
		//	printf("\nSPECIAL_CHAR hooked.SO WHAT..?\n");
	return (0);
}

char	*ft_read_input(int fd, t_term *term, t_list *log)
{
	t_input				user;
	int					bytes;

	user.log_size = ft_lstsize(log);
	user.i = user.log_size;
	user.input = ft_strdup("");
	if (user.input == NULL)
		return (NULL);
	user.screen = user.input;
	ft_print_prompt(term);
	while ((bytes = read(fd, user.buf, 4)))
	{
		user.buf[bytes] = '\0';
		if (user.buf[0] == '\n')
		{
			if (user.i < user.log_size)
				free(user.input);
			return (user.screen);
		}
		else
			ft_screen_wrapper(&user, log);
		tputs(tparm(term->ch, ft_strlen("Minishell_says$ ")), 1, ft_termcap_on);
		tputs(term->ce, 1, ft_termcap_on);
		write(1, user.screen, ft_strlen(user.screen));
	}
	return (NULL);
}

int		ft_isempty(char *str)
{
	while (*str)
	{
		if (*str != ' ')
			return (0);
		str++;
	}
	return (1);
}

int		ft_edit_line(char **screen, char *buf, unsigned int s_len)
{
	char *to_free;

	to_free = NULL;

	if (buf[0] == 127 && **screen != '\0')
		(*screen)[s_len - 1] = '\0';
	else
	{
		to_free = *screen;
		*screen = ft_strjoin(*screen, buf);
		if (to_free)
			free(to_free);
		if (*screen == NULL)
			return (-1);
	}
	return (1);
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

	prompt = "Minishell_says$ ";
	//Mets le prompt en gras
	tputs(term->md, 1, ft_termcap_on);
	//Souligne le prompt
	//tputs(term->us, 1, ft_termcap_on);
	//Choisir la couleur du prompt
	tputs(tparm(term->AF, COLOR_BLUE), 1, ft_termcap_on);
	ft_putstr(prompt);
	//Reset les settings d'ecriture
	tputs(term->me, 1, ft_termcap_on);
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
}

char	*ft_strndup(char *src, int len)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(sizeof(*dest) * (len + 1));
	if (dest == NULL)
		return (NULL);
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int		ft_down_arrow(char **screen, char **user_input, 
								t_list *log, unsigned int *i)
{
	unsigned int log_size;
	
	log_size = ft_lstsize(log);
	if (*i < log_size - 1)
	{
		free(*screen);
		(*i)++;
		*screen = ft_strdup((char *)((ft_lstat(log, *i))->content));
	}
	else if (*i == log_size -1)
	{
		free(*screen);
		*screen = *user_input;
		(*i)++;
	}
	if (*screen == NULL)
		return (-1);
	return (1);
}

int		ft_up_arrow(char **screen, char **user_input, 
								t_list *log, unsigned int *i)
{
	unsigned int log_size;

	log_size = ft_lstsize(log);
//	printf("\nUP_ARROW hooked\n");
	//Save user_input avant de mettre screen sur history
	if (*i == log_size)
		*user_input = *screen;
	//Screen est une copie de history et va changer, donc on free
	//Opti possible
	if (*i < log_size)
		free(*screen);
	if (*i > 0)
		*i -= 1;

	//Remonte l'historique seulement si il reste de l'historique
	*screen = ft_strdup(((char *)((ft_lstat(log, *i))->content)));
	if (*screen == NULL)
		return (-1);
	return (1);
}

int		ft_update_log(char **screen, t_list *log, int fd_log)
{
	char			*last_log;
	unsigned int	log_size;
	unsigned int	s_len;
	t_list			*new;

	s_len = ft_strlen(*screen);
	log_size = ft_lstsize(log);
	last_log = (char *)((ft_lstat(log, log_size - 1))->content);
	if (ft_strcmp(*screen, last_log) && !ft_isempty(*screen))
	{
		write(fd_log, *screen, s_len);
		write(fd_log, "\n", 1);
		new = ft_lstnew(ft_strdup(*screen));
		if (new == NULL)
			return (-1);
		ft_lstadd_back(&log, new);
	}
	//Mauvaise idee si echo - n ??
	write(1, "\n", 1);
	return (2);
}
