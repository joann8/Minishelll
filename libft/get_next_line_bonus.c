/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 10:30:02 by jacher            #+#    #+#             */
/*   Updated: 2021/03/10 13:50:50 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		check_error(int fd, char **line)
{
	if (fd < 0)
		return (-1);
	if (!line)
		return (-1);
	if (BUFFER_SIZE < 1)
		return (-1);
	return (0);
}

char	*update_str(char *str, int *res)
{
	char			*tmp;
	unsigned int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\n' && str[i])
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	if (!(tmp = malloc(sizeof(char) * (ft_strlen_gnl(str) - i + 1))))
	{
		*res = -1;
		return (NULL);
	}
	i++;
	cpy_update(str, tmp, i);
	free(str);
	return (tmp);
}

char	*create_line(char *str, int *res)
{
	char			*tmp;
	unsigned int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (!(tmp = malloc((sizeof(char) * (i + 1)))))
	{
		*res = -1;
		return (NULL);
	}
	i = 0;
	while (str[i] != '\n' && str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int		return_neg(char **line, char *str, char *buf)
{
	if (line)
		*line = NULL;
	if (str)
		free(str);
	if (buf)
		free(buf);
	return (-1);
}

int		get_next_line(int fd, char **line)
{
	static char		*str[256];
	char			*buf;
	int				bytes;
	int				res;

	res = 1;
	if ((check_error(fd, line) == -1) ||
			!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	bytes = BUFFER_SIZE;
	while (bytes > 0 && ft_chrn(str[fd]) == 0)
	{
		if ((bytes = read(fd, buf, BUFFER_SIZE)) == -1)
			return (return_neg(line, str[fd], buf));
		buf[bytes] = '\0';
		str[fd] = ft_strjoin_gnl(str[fd], buf, &res);
		if (res == -1)
			return (return_neg(line, str[fd], buf));
	}
	free(buf);
	*line = create_line(str[fd], &res);
	str[fd] = update_str(str[fd], &res);
	if (res == -1)
		return (return_neg(line, str[fd], buf));
	return ((bytes == 0 ? 0 : 1));
}
