/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 20:36:57 by mpetruno          #+#    #+#             */
/*   Updated: 2019/01/06 20:41:49 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

int		init_cursor(void)
{
	g_shell.positions.prompt.col = 0;
	g_shell.positions.prompt.row = 0;
	g_shell.positions.cmd.col = 0;
	g_shell.positions.cmd.row = 0;
	g_shell.positions.current.col = 0;
	g_shell.positions.current.row = 0;
	return (0);
}

void	set_cursor(t_cursor *cursor)
{
	char	buff[16];
	char	*ptr;
	int		n;
	int		x;
	int		y;

	if (g_shell.canonical)
		return ;
	n = 0;
	ft_putstr("\x1b[6n");
	while (read(0, buff + n, 1))
	{
		if (buff[n] == 'R')
			break ;
		n++;
	}
	ptr = ft_strchr(buff + 2, ';');
	y = ft_atoi(buff + 2) - 1;
	x = ft_atoi(ptr + 1) - 1;
	if (x < 0 || y < 0)
		return ;
	cursor->row = y;
	cursor->col = x;
}
