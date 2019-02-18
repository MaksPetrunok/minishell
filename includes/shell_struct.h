/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 07:04:27 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/18 09:38:57 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_STRUCT_H
# define SHELL_STRUCT_H

# include "libft.h"
# include "input.h"
# include "environ.h"
# include "cursor.h"
# include "history.h"
# include "lexer.h"
# include <sys/ioctl.h>

typedef	struct		s_process
{
	pid_t			pid;
}					t_process;

typedef struct		s_shell
{
	struct termios	*term_typing;
	struct termios	*term_default;
	enum e_state	inp_state;	// input state
	char			*const_input;	// constant buffer
	int				run;
	int				canonical;
	int				last_ret;
	int				plen;
	t_inp_buff		*input;
	t_env			*environ;
	t_positions		positions;
	struct winsize	winsize;
	t_history		*history;
	t_list			*childs;
	char			*clipboard;
}					t_shell;

/*
** shell.c
*/
int					init_shell(char **env);
void				exit_shell(void);

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
