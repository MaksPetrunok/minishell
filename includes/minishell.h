/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 17:49:54 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/30 21:38:10 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "environ.h"
# include "err.h"
# include "builtin.h"
# include "lexer.h"

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>

# define SHELL_NAME	"SmashMyBashUp"
# define CMD_DELIM	';'

extern pid_t	g_child;

void	show_prompt(void);
char	**get_input(void);
t_token	*tokenize(char *s);
char	**parse_cmd(t_token **tkn);

/*
** Freeing allocated data.
*/

void	tknlst_free(t_token *lst);
void	arr_free(void **av);
void	env_free(t_env *env);

int		execute(char **av);

void	setup_signals(void);
void	sh_sig_handler(int sig);

#endif
