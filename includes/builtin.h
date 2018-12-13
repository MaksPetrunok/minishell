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

# define BUILTINS_BUFF_SIZE	10

typedef	int	(*t_func)(char **);

t_func	get_builtin(const char *name);
char	**get_builtin_list(char **list);

int		builtin_exit(char **av);
int		builtin_pwd(char **av);
int		builtin_cd(char **av);
int		builtin_env(char **av);
int		builtin_setenv(char **av);
int		builtin_unsetenv(char **av);
int		builtin_echo(char **av);

#endif
