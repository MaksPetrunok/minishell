/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:40:28 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/10 03:50:40 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	append_newline(char **av)
{
	av++;
	if (*av == NULL)
		return (1);
	if (ft_strcmp(*av, "-n") == 0)
		return (0);
	return (1);
}

int			builtin_echo(char **av)
{
	int	append_nl;
	int	i;
	int	size;

	size = ft_arrsize((void **)av);
	append_nl = append_newline(av);
	if (append_nl)
		i = 1;
	else
		i = 2;
	while (i < size)
	{
		ft_putstr(av[i]);
		if (size - i > 1)
			write(1, " ", 1);
		i++;
	}
	if (append_nl)
		write(1, "\n", 1);
	return (1);
}
