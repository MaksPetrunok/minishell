/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:41:19 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/18 11:07:11 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unsetenv(char **av)
{
	int	i;

	if (ft_arrsize((void **)av) < 2)
	{
		ft_putstr_fd("setenv: too few arguments\n", 2);
		g_shell.last_ret = 1;
		return (-1);
	}
	i = 1;
	while (av[i] != 0)
		unset_var(av[i++], g_shell.environ);
	g_shell.last_ret = 0;
	return (1);
}
