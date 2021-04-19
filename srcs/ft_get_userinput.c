/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_userinput.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 10:30:02 by jacher            #+#    #+#             */
/*   Updated: 2021/04/19 16:08:38 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int	ft_get_userinput(char **line, char *prompt, char *log_path)
{
	t_term			term;
	t_list			*log;
	int				fd_log;
	struct termios	origin;
	
	log = NULL;
	fd_log = open(log_path, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (fd_log < 0)
	{
		printf("fd_log return == -1, errno = %s\n", strerror(errno));
		return (-1); // Err opening
	}
	if (ft_make_loglst(&log, fd_log) < 0)
	{
		ft_lstclear(&log, free);
		return (-1);
	}
	ft_enable_raw_mode(&origin);
	if (ft_init_termcap(&term))
	{
		ft_lstclear(&log, free);
		printf("termcap init failed\n");
		return (-1);
	}
	*line = ft_read_input(STDIN_FILENO, &term, log, prompt);
	tputs(term.me, 1, ft_termcap_on);
	ft_disable_raw_mode(&origin);
	if (*line == NULL || ft_update_log(line, log, fd_log) == -1
			|| close(fd_log) < 0)
	{
		ft_lstclear(&log, free);
		printf("error in ft_read_input\n");
		return (-1);
	}
	ft_lstclear(&log, free);
	return (0);
}

int	ft_init_input(t_input *user, t_term *term, t_list *log, char *prompt)
{
	user->log_size = ft_lstsize(log);
	user->i = user->log_size;
	user->input = ft_strdup("");
	if (user->input == NULL)
		return (-1);
	user->screen = user->input;
	ft_print_prompt(term, prompt);
	tputs(term->sc, 1, ft_termcap_on);
	return (0);
}

char	*ft_read_input(int fd, t_term *term, t_list *log, char *prompt)
{
	t_input				user;

	if (ft_init_input(&user, term, log, prompt) == -1)
		return (NULL);
	while ((user.bytes = read(fd, user.buf, 4)) > 0)
	{
		user.buf[user.bytes] = '\0';
		if (user.buf[0] == '\n')
		{
			if (user.i < user.log_size)
				free(user.input);
			return (user.screen);
		}
		else if (user.buf[0] == 12)
			ft_move_cursor_home(term, prompt);
		else
			ft_screen_wrapper(&user, log);
		if (ft_is_endofscreen(term, prompt))
		{
			free(user.screen);
			if (user.input)
				free(user.input);
			return (NULL);
		}
		tputs(term->rc, 1, ft_termcap_on);
		tputs(term->cd, 1, ft_termcap_on);
		write(1, user.screen, ft_strlen(user.screen));
	}
	free(user.screen);
	if (user.input)
		free(user.input);
	return (NULL);
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

int		ft_make_loglst(t_list **head, int fd)
{
	t_list	*new_node;
	char	*line;
	char	*log;

	new_node = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		new_node = ft_lstnew(NULL);
		if (new_node == NULL)
			return (-1);
		ft_lstadd_back(head, new_node);
		log = ft_strdup(line);
		free(line);
		if (log == NULL)
			return (-1);
		new_node->content = log;
	}
	free(line);
	return (0);
}

void	ft_print_prompt(t_term *term, char *prompt)
{
	int i;
	int color;

	i = 0;
	color = 1;
	while (prompt[i])
	{
		if (prompt[i] == '$' && prompt[i + 2] == '\0')
			tputs(ANSI_WHITE, 1, ft_termcap_on);
		else if (color == 1 && prompt[i] == ':')
		{
			tputs(ANSI_WHITE, 1, ft_termcap_on);
			color = 2;
		}
		else if (color == 1)
			tputs(ANSI_BOLD_RED, 1, ft_termcap_on);
		else if (color == 2)
			tputs(ANSI_BOLD_YELLOW, 1, ft_termcap_on);
		ft_putchar(prompt[i]);
		i++;
		tputs(term->me, 1, ft_termcap_on);
	}
}
