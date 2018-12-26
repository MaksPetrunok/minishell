/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 17:49:54 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/18 14:36:16 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "shell_struct.h"
# include "libft.h"
# include "input.h"
# include "environ.h"
# include "err.h"
# include "builtin.h"
# include "lexer.h"
# include "autocomp.h"
# include "cursor.h"
# include "history.h"

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>

# include <termios.h>
# include <termcap.h>
# include <term.h>

# define SHELL_NAME	"SmashMyBashUp"
# define UNUSED	__attribute__((unused))

extern t_shell	g_shell;

void	show_prompt(void);
t_token	*tokenize(char *s);
char	**parse_cmd(t_token **tkn);

/*
** Freeing allocated data.
*/

void	tknlst_free(t_token *lst);
void	arr_free(void **av);
void	env_free(t_env *env);

int		execute(char **av, t_env *env);

void	setup_signals(void);
void	sh_sigint_handler(int sig);

#endif
