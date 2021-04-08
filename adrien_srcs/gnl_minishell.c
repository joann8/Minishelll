/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 10:30:02 by jacher            #+#    #+#             */
/*   Updated: 2021/04/08 14:03:13 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"
#include <term.h>

/*
void	enable_raw_mode(struct termios *origin)
{
	struct termios *raw;

	raw = origin;
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
	char	buf[5];
	char	*line;
	int		count;
	int		bytes;
//	struct termios origin;

	line = malloc(sizeof(char) * 1); // alloue l'espace pour le end of str
	if (line == NULL) 
	{
		*res = -1; //erreur malloc
		return (NULL);
	}
	count = 0;
	line[0] = '\0';
	while ((bytes = read(0, buf, 4)) > 0)
	{
		buf[bytes] = '\0';
		printf("\ncount = %d | buf = %d \n", count, buf);
		if (buf[0] == '\n')
			break;
		else if (ft_isprint(*buf) == 1)
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
	}
	*res = 0;
	return (line);
}
*/

int		ft_init_termcap_type(void)
{
	char	*term_name;
	int		ret;

	term_name = getenv("TERM");
	if (term_name == NULL)
	{
		printf("env '$TERM' not found\n");
		return (1);
	}
	ret = tgetent(NULL, term_name);
	if (ret == 0)
	{
		printf("tgetent == 0\n");
		return (1);
	}
	else if (ret == -1)
	{
		printf("terminfo '%s' database not found\n", term_name);
		return (-1);
	}
	printf("Init success. Terminal name = %s\n", term_name);
	return (0);
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	//struct termios raw;
	//char	*line;

	/*
	enable_raw_mode(&raw);
	line = gnl_minishell(&res);
	disable_raw_mode(&origin);
	printf("\n***main***\nstr:\n|%s|\nres: %d\n", line, res);
	*/
	if (ft_init_termcap_type())
		return (printf("termcap init failed\n"));
	return (0);
}
