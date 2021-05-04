/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacher <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:25:25 by jacher            #+#    #+#             */
/*   Updated: 2021/05/04 09:47:50 by jacher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H

# define STRUCT_H

typedef	struct				s_process
{
	int						fd;
	int						exit_status;
}							t_process;

typedef	enum				e_type
{
	WORD,
	FILENAME,
	SEPARATOR,
	PIPE,
	IN,
	OUT,
	APPEND
}							t_e_type;

typedef struct				s_token
{
	t_e_type				e_type;
	char					*tok_str;
}							t_token;

typedef struct				s_seq
{
	t_list					*word;
	t_list					*redir;
	int						pipe_total;
	int						pipe_pos;
	struct s_seq			*next_pipe;
}							t_seq;

typedef struct				s_redir
{
	t_e_type				e_type;
	char					*file_name;
}							t_redir;

typedef struct				s_pipe
{
	int						size;
	int						fd_in_to_use;
	int						fd_out_to_use;
}							t_pipe;

typedef struct				s_simple_cmd
{
	char					*job;
	char					**av;
	int						ac;
	int						fd_in;
	int						fd_out;
	int						pipe_pos;
	t_pipe					p;
	int						on;
	struct s_simple_cmd		*next_pipe;
}							t_simple_cmd;

typedef struct				s_var
{
	char					*name;
	char					*value;
	int						on;
}							t_var;

typedef	struct				s_term
{
	int						col;
	int						line;
	int						*t_ret;
	char					*name;
	char					*cm;
	char					*me;
	char					*rc;
	char					*sc;
	char					*cd;
}							t_term;

typedef	struct				s_input
{
	unsigned int			i;
	unsigned int			log_size;
	int						bytes;
	char					buf[5];
	char					*screen;
	char					*input;
}							t_input;

typedef struct				s_expansion
{
	char					*str;
	char					*var_str;
	char					*tmp;
	int						i;
	int						j;
	int						quote;
	int						mod;
}							t_expansion;

#endif
