/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 07:04:27 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/18 14:36:00 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_STRUCT_H
# define SHELL_STRUCT_H

# include "libft.h"
# include "input.h"
# include "environ.h"
# include <sys/ioctl.h>

typedef	struct		s_process
{
	pid_t			pid;
}					t_process;

typedef struct		s_cusor
{
	int				row;
	int				col;
}					t_cursor;

typedef struct		s_shell
{
	struct termios	*term_typing;
	struct termios	*term_default;
	int				run;
	int				canonical;
	int				last_ret;
	t_inp_buff		*input;
	t_env			*environ;
	t_cursor		*cursor;
	struct winsize	w;
	t_list			*childs;
}					t_shell;

/*
** shell.c
*/
int					init_shell(char **env);
void				exit_shell(void);

/*
** cursor.c
*/
int					init_cursor(void);

/*
** terminal.c
*/
int					switch_term_to(struct termios *term);
int					setup_terminal(void);
void				free_terminals(void);

/*
** shell_exit.c
*/
int					finish_child_processes(void);
int					add_child_process(pid_t pid);

#endif
