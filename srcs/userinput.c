/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   userinput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 10:30:02 by jacher            #+#    #+#             */
/*   Updated: 2021/04/20 15:02:27 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int	ft_first_init_userinput(int fd_log, t_term *term, t_list **log
								, struct termios *origin)
{
	if (fd_log < 0)
	{
		printf("fd_log return == -1, errno = %s\n", strerror(errno));
		return (-1); // Err opening
	}
	if (ft_make_loglst(log, fd_log) < 0)
	{
		ft_lstclear(log, free);
		return (-1);
	}
	ft_enable_raw_mode(origin);
	if (ft_init_termcap(term))
	{
		ft_lstclear(log, free);
		printf("termcap init failed\n");
		return (-1);
	}
	return (0);
}

int	ft_second_init_userinput(t_input *user, t_term *term, t_list *log, char *prompt)
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

int		ft_handle_input(t_input *user, t_term *term, char *prompt, t_list *log)
{
	if (user->buf[0] == '\n')
		{
			if (user->i < user->log_size && user->input)
				free(user->input);
			return (0);
		}
		else if (user->buf[0] == 12)
			ft_move_cursor_home(term, prompt);
		else
		{
			if (ft_screen_wrapper(user, log) == -1)
				return (-1);
		}
		if (ft_is_endofscreen(term, prompt) == -1)
			return (-1);
		tputs(term->rc, 1, ft_termcap_on);
		tputs(term->cd, 1, ft_termcap_on);
		write(1, user->screen, ft_strlen(user->screen)); // calculer si endofscreen ?
		return (1);
}

char	*ft_read_input(int fd, t_term *term, t_list *log, char *prompt)
{
	t_input				user;
	int					ret;

	if (ft_second_init_userinput(&user, term, log, prompt) == -1)
		return (NULL);
	while ((user.bytes = read(fd, user.buf, 4)) > 0)
	{
		user.buf[user.bytes] = '\0';
		ret = ft_handle_input(&user, term, prompt, log);
		if (ret == -1) //err malloc
			break;
		else if (ret == 0)
			return (user.screen);
	}
	free(user.screen);
	if (user.input)
		free(user.input);
	return (NULL);
}

int	ft_get_userinput(char **line, char *prompt, char *log_path)
{
	t_term			term;
	t_list			*log;
	int				fd_log;
	struct termios	origin;
	
	log = NULL;
	fd_log = open(log_path, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (ft_first_init_userinput(fd_log, &term, &log, &origin) == -1)
		return (-1);
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

