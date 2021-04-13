/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calao <adconsta@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 16:09:20 by calao             #+#    #+#             */
/*   Updated: 2021/04/13 16:22:59 by calao            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft.h"

char	*ft_my_getcwd(void)
{
	char	*cwd;
	size_t	size;
	int		i;

	size = 10;
	cwd = NULL;
	i = 0;
	while (cwd == NULL)
	{
		cwd = getcwd(cwd, size);
		if (cwd == NULL)
		{
			printf("tour %d\n", i);
			if (errno == ERANGE)
				size += 20;
			else
				return (NULL);
		}
		i++;
	}
	return (cwd);
}


int		ft_relative_to_absolute(char *r_path)
{
	char	*cwd;

	cwd = ft_my_getcwd();
	if (cwd == NULL)
		return (-1);
	r_path = cwd;
	printf("cwd = %s\n", r_path);
	free(cwd);
	return (0);
}

