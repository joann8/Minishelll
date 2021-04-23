/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   userinput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 10:30:02 by jacher            #+#    #+#             */
/*   Updated: 2021/04/23 12:18:58 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int	ft_first_init_userinput(int fd_log, t_term *term, t_list **log
								, struct termios *origin)
{
	if (fd_log < 0)
		return (-1); // Err opening
	if (ft_make_loglst(log, fd_log) < 0)
	{
		ft_lstclear(log, free);
		return (-1);
	}
	ft_enable_raw_mode(origin);
	if (ft_init_termcap(term))
	{
		ft_lstclear(log, free);
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

int		ft_handle_key_catching(t_input *user, t_term *term, char *prompt, t_list *log)
{
	if (user->buf[0] == 4 && ft_strlen(user->screen) == 0)
	{
		g.exit_status = 0;
		ft_putstr_fd("exit\n", 1);
		return (-227);
	}	
	else if (user->buf[0] == '\n')
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
	if (ft_is_endofscreen(term, prompt, user) == -1)
		return (-1);
	tputs(term->rc, 1, ft_termcap_on);
	tputs(term->cd, 1, ft_termcap_on);
	write(1, user->screen, ft_strlen(user->screen)); // calculer si endofscreen ?
	return (1);
}

char	*ft_read_input(int fd, t_term *term, t_list *log, char *prompt)
{
	t_input				user;

	if (ft_second_init_userinput(&user, term, log, prompt) == -1)
		return (NULL);
	while ((user.bytes = read(fd, user.buf, 4)) > 0)
	{
		user.buf[user.bytes] = '\0';
		*term->t_ret = ft_handle_key_catching(&user, term, prompt, log);
		if (*term->t_ret < 0) //err malloc ou  CTRL D
			break;
		else if (*term->t_ret == 0)
			return (user.screen);
	}
	free(user.screen);
	if (user.i < user.log_size && user.input)
		free(user.input);
	return (NULL);
}

int	ft_get_userinput(char **line, char *prompt, char *log_path, int *ret)
{
	t_term			term;
	t_list			*log;
	int				fd_log;
	struct termios	origin;
	
	log = NULL;
	term.t_ret = ret;
	fd_log = open(log_path, O_RDWR | O_CREAT | O_APPEND, 0777);
	if (ft_first_init_userinput(fd_log, &term, &log, &origin) == -1)
		return (-1);
	g.fd = dup(STDIN_FILENO);
	*line = ft_read_input(g.fd, &term, log, prompt);
	tputs(term.me, 1, ft_termcap_on);
	ft_disable_raw_mode(&origin);
	if (*ret == -227 || *line == NULL 
			|| ft_update_log(line, log, fd_log) == -1)
	{
		if (close(fd_log) < 0)
			*ret = -1;
		ft_lstclear(&log, free);
		return (*ret);
	}
	*ret = 0;
	if (close(fd_log) < 0)
		*ret = -1;
	ft_lstclear(&log, free);
	return (*ret);
}
