/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:25:25 by jacher            #+#    #+#             */
/*   Updated: 2021/04/09 13:06:50 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H

# define STRUCT_H

typedef	enum	e_type
{
	WORD,
	FILENAME,
	SEPARATOR,
	PIPE,
	IN,
	OUT,
	APPEND
}				t_e_type;

typedef struct	s_token
{
	int		e_type;
	char	*tok_str;
}				t_token;

typedef struct		s_seq
{
	t_list		 	*word;
	t_list			*redir;
	int				pipe_total;
	int				pipe_pos;
	struct s_seq	*next_pipe;
}					t_seq;

typedef struct		s_redir
{
	int				e_type;
	char			*file_name;
}					t_redir;

typedef struct		s_simple_cmd
{
	char			*job;
	char			**av;
	int				ac;
	int				fd_tab[2];
	int				fd_in;
	int				fd_out;
}					t_simple_cmd;

typedef struct		s_var
{
	char			*name;
	char			*value;
}					t_var;
	
#endif
