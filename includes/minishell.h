/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 17:49:54 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 19:09:06 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "shell_struct.h"
# include "libft.h"
# include "hashmap.h"
# include "input.h"
# include "environ.h"
# include "err.h"
# include "builtin.h"
# include "lexer.h"
# include "parser.h"
# include "exec.h"
# include "ast.h"
# include "autocomp.h"
# include "cursor.h"
# include "history.h"

# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>

# include <termios.h>
# include <termcap.h>
# include <term.h>

# define SHELL_NAME	"zbsh"
# define BINARY_HASHMAP_SIZE 2048
# define UNUSED	__attribute__((unused))

extern t_shell	g_shell;

void	show_prompt(void);

/*
** Freeing allocated data.
*/

void	tknlst_free(t_token *lst);
void	arr_free(void **av);
void	env_free(t_env *env);

void	setup_signals(void);
void	sh_sigint_handler(int sig);

/*
** main_aux.c
*/
int		process_input(char *input);
char	*combine_input(char *inp);
void	add_newline(void);

#endif
