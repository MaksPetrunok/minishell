/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:49:19 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/13 19:51:03 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "environ.h"

# define BUILTINS_BUFF_SIZE	10

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

#endif
