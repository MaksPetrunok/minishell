/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 17:42:37 by mpetruno          #+#    #+#             */
/*   Updated: 2019/01/06 17:42:39 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

void	clear_from_cursor(t_inp_buff *buff)
{
	(void)buff;
	if (g_shell.positions.current.row < g_shell.winsize.ws_row - 1)
	{
		move_cursor(0, g_shell.positions.current.row + 1);
		tconf("cd");
		move_cursor(g_shell.positions.current.col,
					g_shell.positions.current.row);
	}
	tconf("ce");
}
