/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   userinput_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:51:00 by calao             #+#    #+#             */
/*   Updated: 2021/04/21 18:24:26 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		ft_screen_wrapper(t_input *user, t_list *log)
{
	unsigned int	s_len;
	int				ret;
	
	ret = 0;
	s_len = ft_strlen(user->screen);
	if ( user->bytes == 1 && (ft_isprint(user->buf[0]) || user->buf[0] == 127))
		{
			if (ft_edit_line(&(user->screen), user->buf, s_len) == -1)
				return (-1); // Malloc error;
			if (user->i == user->log_size)
			   user->input = user->screen;// verifier pertinence ou leaks
		}
		else if (user->buf[0] == 27 && user->buf[1] == '[' && user->buf[2] == 'B')
			ret = ft_down_arrow(&(user->screen), &(user->input), log, &(user->i));
		else if (user->buf[0] == 27 && user->buf[1] == '[' && user->buf[2] == 'A')
			ret = ft_up_arrow(&(user->screen), &(user->input), log, &(user->i));
	return (0);
}

int		ft_edit_line(char **screen, char *buf, unsigned int s_len)
{
	char *to_free;

	to_free = NULL;

	if (buf[0] == 127 && **screen != '\0')
		(*screen)[s_len - 1] = '\0';
	else if (ft_isprint(buf[0]))
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
	if (*i == log_size)
		*user_input = *screen; // BETISE non ? faut il free user_input?
	if (*i < log_size)
		free(*screen);
	if (*i > 0)
		*i -= 1;
	*screen = ft_strdup(((char *)((ft_lstat(log, *i))->content)));
	if (*screen == NULL)
		return (-1);
	return (1);
}
