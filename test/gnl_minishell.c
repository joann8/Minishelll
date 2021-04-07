/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 10:30:02 by jacher            #+#    #+#             */
/*   Updated: 2021/04/07 10:51:43 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	enable_raw_mode(struct termios *raw)
{
	//struct termios raw;

	tcgetattr(STDIN_FILENO, raw);
	raw->c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, raw);
}

void	disable_raw_mode(struct termios *origin)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, origin);
}

char *gnl_minishell(int *res)
{
	char	buf;
	char	*line;
	int		count;
	struct termios raw;
//	struct termios origin;

	enable_raw_mode(&raw);
	line = malloc(sizeof(char) * 1); // alloue l'espace pour le end of str
	if (line == NULL) 
	{
		*res = -1; //erreur malloc
		return (NULL);
	}
	count = 0;
	line[0] = '\0';
	while (read(STDIN_FILENO, &buf, 1) == 1)
	{
		printf("\ncount = %d | buf = %d \n", count, buf);
		if (buf == '\n')
			break;
		else if (ft_isprint(buf) == 1)
		{
			write(1, &buf, 1);
			line = realloc(line, sizeof(char) * (count + 2));
			if (line == NULL)
			{
				*res = -1;
				return (NULL);
			}
			line[count] = buf;
			line[count + 1] = '\0';
			count ++;
		}
		
		/*else if (buf == 27)
		{
			read(STDIN_FILENO, &buf, 1);
			read(STDIN_FILENO, &buf, 1);
		}*/
	}
	*res = 0;
	//disable_raw_mode(&origin);
	return (line);
}

int main()
{
	int res;
	char *line;

	res = 42;
	line = gnl_minishell(&res);
	printf("\n***main***\nstr:\n|%s|\nres: %d\n", line, res);
	return (0);
}
