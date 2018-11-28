/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:49:19 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/28 18:51:02 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef	int	(*t_func)(char **);

t_func	get_builtin(const char *name);

int		builtin_exit(char **av);
int		builtin_pwd(char **av);
int		builtin_cd(char **av);
int		builtin_env(char **av);
int		builtin_setenv(char **av);
int		builtin_unsetenv(char **av);
int		builtin_echo(char **av);

#endif
