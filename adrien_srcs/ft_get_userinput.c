/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_userinput.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 10:30:02 by jacher            #+#    #+#             */
/*   Updated: 2021/04/14 11:30:00 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int	ft_get_userinput(char **line, char *cwd)
{
	t_term			term;
	t_list			*log;
	int				fd_log;
	struct termios	origin;
	
	log = NULL;
	fd_log = open("minishell.log", O_RDWR | O_CREAT | O_APPEND, 0666);
	
	//Init la historique de cmd
	if (fd_log < 0)
		return (-1); // Err opening
	if (ft_make_loglst(&log, fd_log) < 0)
		return (-1);

	//Initialise la librairie termcap avec la var $TERM
	ft_enable_raw_mode(&origin);
	if (ft_init_termcap(&term))
		return (-(printf("termcap init failed\n")));
	
	*line = ft_read_input(STDIN_FILENO, &term, log, cwd);
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

char	*ft_read_input(int fd, t_term *term, t_list *log, char *cwd)
{
	t_input				user;
	int					bytes;

	user.log_size = ft_lstsize(log);
	user.i = user.log_size;
	user.input = ft_strdup("");
	if (user.input == NULL)
		return (NULL);
	user.screen = user.input;
	ft_print_prompt(term, cwd);
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

void	ft_print_prompt(t_term *term, char *cwd)
{
	char *prompt;

	prompt = "Minishell_says$ ";
	//Mets le prompt en gras
	tputs(term->md, 1, ft_termcap_on);
	//Souligne le prompt
	//tputs(term->us, 1, ft_termcap_on);
	//Choisir la couleur du prompt
	tputs(tparm(term->AF, COLOR_GREEN), 1, ft_termcap_on);
	ft_putstr(prompt);
	tputs(tparm(term->AF, COLOR_WHITE), 1, ft_termcap_on);
	ft_putstr(":");
	tputs(tparm(term->AF, COLOR_BLUE), 1, ft_termcap_on);
	ft_putstr(cwd);
	//Reset les settings d'ecriture
	tputs(term->me, 1, ft_termcap_on);
}
