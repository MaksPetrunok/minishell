/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:49:19 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 20:22:57 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "environ.h"

# define BUILTINS_BUFF_SIZE	10

# define US_CD "usage: cd | cd - | cd -- | cd [path]"
# define US_ECHO "usage: echo [arguments...]"
# define US_SETENV "usage: setenv name value | setenv name=value"
# define US_UNSETENV "usage: unsetenv [name..]"
# define US_ENV "usage: env [-i] [-u name] [command]"
# define US_EXIT "usage: exit | exit [status]"
# define US_UI "See file 'help' for input editing hot keys."

# define HELP "usage: help [command name]"

typedef	int	(*t_func)(char **, t_env *);

t_func	get_builtin(const char *name);
char	**get_builtin_list(char **list);

int		builtin_exit(char **av, t_env *e);
int		builtin_pwd(char **av, t_env *e);
int		builtin_cd(char **av, t_env *e);
int		builtin_env(char **av, t_env *e);
int		builtin_setenv(char **av, t_env *e);
int		builtin_unsetenv(char **av, t_env *e);
int		builtin_echo(char **av, t_env *e);
int		builtin_help(char **av, t_env *e);

#endif
