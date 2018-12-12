/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:41:19 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/12 16:02:16 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

int	builtin_unsetenv(char **av)
{
	if (ft_arrsize((void **)av) < 2)
	{
		ft_putstr_fd("setenv: too few arguments\n", 2);
		g_shell.last_ret = 1;
		return (-1);
	}
	if (av[1] != 0)
		unset_var(av[1]);
	g_shell.last_ret = 0;
	return (1);
}
