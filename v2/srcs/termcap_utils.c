/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 09:58:48 by calao             #+#    #+#             */
/*   Updated: 2021/04/21 22:11:05 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

int		ft_is_endofscreen(t_term *term, char *prompt, t_input *user)
{
	int		cur_row;
	int		cur_col;
	int		len_left;

	if (ft_getcursorxy(&cur_row, &cur_col))
		return (-1);
	len_left = term->col - (int)ft_strlen(prompt);
	if ((cur_row == term->line && cur_col == term->col)
			|| (cur_row == term->line 
				&& len_left < (int)ft_strlen(user->screen)))
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
