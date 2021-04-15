/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_userinput.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 10:30:02 by jacher            #+#    #+#             */
/*   Updated: 2021/04/15 22:18:09 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

#define ANSI_WHITE			"\E[0;37m"
#define ANSI_BOLD_WHITE		"\E[1;37m"
#define ANSI_BOLD_RED		"\E[1;31m"
#define ANSI_BOLD_YELLOW	"\E[1;33m"

int	ft_get_userinput(char **line, char *prompt, char *log_path)
{
	t_term			term;
	t_list			*log;
	int				fd_log;
	struct termios	origin;
	
	log = NULL;
	fd_log = open(log_path, O_RDWR | O_CREAT | O_APPEND, 0666);
	
	//Init la historique de cmd
	if (fd_log < 0)
	{
		printf("fd_log return == -1, errno = %s\n", strerror(errno));
		return (-1); // Err opening
	}
	if (ft_make_loglst(&log, fd_log) < 0)
		return (-1);
	//Initialise la librairie termcap avec la var $TERM
	ft_enable_raw_mode(&origin);
	if (ft_init_termcap(&term))
		return (-(printf("termcap init failed\n")));
//	ft_print_prompt(&term, prompt);
	*line = ft_read_input(STDIN_FILENO, &term, log, prompt);
	tputs(term.me, 1, ft_termcap_on);
	ft_disable_raw_mode(&origin);
	
	if (*line == NULL)
		return (printf("error in get_raw_input\n"));
	if (ft_update_log(line, log, fd_log) == -1)
		return (-1); // Err malloc
	if (close(fd_log) < 0)
		return (-1);
	ft_lstclear(&log, free);
	return (1);
}

char	*ft_read_input(int fd, t_term *term, t_list *log, char *prompt)
{
	t_input				user;
	int					bytes;

	user.log_size = ft_lstsize(log);
	user.i = user.log_size;
	user.input = ft_strdup("");
	if (user.input == NULL)
		return (NULL);
	user.screen = user.input;
	printf("col = %d\n", term->col);
	printf("row = %d\n", term->line);
	ft_print_prompt(term, prompt);
	tputs(term->sc, 0, ft_termcap_on);
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
		tputs(term->rc, 1, ft_termcap_on);
		tputs(term->cd, 1, ft_termcap_on);
		write(1, user.screen, ft_strlen(user.screen));
	}
	return (NULL);
}

int		ft_make_loglst(t_list **head, int fd)
{
	t_list	*new_node;
	char	*line;
	char	*log;

	new_node = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		log = ft_strdup(line);
		free(line);
		if (log == NULL)
			return (-1);
		new_node = ft_lstnew(log);
		if (new_node == NULL)
			return (-1);
		ft_lstadd_back(head, new_node);
	}
	free(line);
	//Recoder une fois pour la derniere ligne ?
	return (0);
}

void	ft_print_prompt(t_term *term, char *prompt)
{
	int i;
	int color;
	int finish;

	i = 0;
	color = 1;
	finish = 0;
	while (prompt[i] && !finish)
	{
		if (prompt[i] == '$' && prompt[i + 2] == '\0')
		{
			tputs(ANSI_WHITE, 1, ft_termcap_on);
			ft_putstr("$ ");
			finish = 1;
		}
		else if (color == 1 && prompt[i] == ':')
		{
			tputs(ANSI_WHITE, 1, ft_termcap_on);
			color = 2;
			ft_putchar(prompt[i]);
		}
		else if (color == 1)
		{
			tputs(ANSI_BOLD_RED, 1, ft_termcap_on);
			ft_putchar(prompt[i]);
		}
		else if (color == 2)
		{
			tputs(ANSI_BOLD_YELLOW, 1, ft_termcap_on);
			ft_putchar(prompt[i]);
		}
		i++;
		tputs(term->me, 1, ft_termcap_on);
	}
}
/* VERSION qui semi fonctionne
char	*ft_read_input(int fd, t_term *term, t_list *log, char *prompt)
{
	t_input				user;
	int					bytes;

	user.log_size = ft_lstsize(log);
	user.i = user.log_size;
	user.input = ft_strdup("");
	if (user.input == NULL)
		return (NULL);
	user.screen = user.input;
	printf("col = %d\n", term->col);
	printf("row = %d\n", term->line);
	tputs(term->sc, 0, ft_termcap_on);
	ft_print_prompt(term, prompt);
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
		//tputs(tgoto(term->ch, 0, 1), 1, ft_termcap_on);
		//write(1, "@", 1);
		tputs(term->rc, 1, ft_termcap_on);
		//tputs(tgoto(term->cm, col, row), 1, ft_termcap_on);
		//write(1, "adrien", 6);
		//tputs(term->ch, 0, ft_termcap_on);
		tputs(term->cd, 1, ft_termcap_on);
		ft_print_prompt(term, prompt);
		write(1, user.screen, ft_strlen(user.screen));
	//	write(1, "\n", 1);
	}
	return (NULL);
}
*/

