/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:40:43 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/18 13:57:48 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

static int	is_number(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str) &&
			*str != '-' &&
			*str != '+' &&
			*str != ' ' &&
			*str != '\t')
			return (0);
		str++;
	}
	return (1);
}

int			builtin_exit(char **arg)
{
	if (arg[1] != NULL)
	{
		if (arg[2] != NULL)
		{
			ft_dprintf(2, "exit: too many arguments\n");
			g_shell.last_ret = 1;
			return (1);
		}
		if (is_number(arg[1]))
			exit(ft_atoi(arg[1]));
		ft_dprintf(2, "exit: numeric argument expected\n");
		return (1);
	}
	return (0);
}
