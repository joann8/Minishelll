/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_userinput_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:51:00 by calao             #+#    #+#             */
/*   Updated: 2021/04/12 11:24:26 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

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
	if (log_size > 0)
		last_log = (char *)((ft_lstat(log, log_size - 1))->content);
	else
		last_log = "";
	if (ft_strcmp(*screen, last_log)
			&& !ft_is_only_space(*screen))
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

