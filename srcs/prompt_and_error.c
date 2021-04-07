/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:27:40 by jacher            #+#    #+#             */
/*   Updated: 2021/04/07 20:17:34 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

void	print_str(char *str)
{
	// pour le prompt : "$ " ou "> "
	write(1, str, ft_strlen(str));
}

int		print_error(int errno, char *error)
{
	(void)errno;
	write(2, error, ft_strlen(error));
	return (-1);
}
