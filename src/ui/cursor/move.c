/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 19:58:48 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/18 11:09:36 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cur_mv_up(void)
{
	if (g_shell.positions.current.row > 0)
	{
		g_shell.positions.current.row--;
		tconf("up");
	}
}

void	cur_mv_down(void)
{
	g_shell.positions.current.row++;
	tconf("do");
}

void	cur_mv_left(void)
{
	if (g_shell.positions.current.col == 0 && g_shell.positions.current.row > 0)
	{
		g_shell.positions.current.col = g_shell.winsize.ws_col - 1;
		g_shell.positions.current.row--;
	}
	else
		g_shell.positions.current.col--;
	move_cursor(g_shell.positions.current.col, g_shell.positions.current.row);
}

void	cur_mv_right(void)
{
	if (g_shell.positions.current.col >= g_shell.winsize.ws_col - 1)
	{
		g_shell.positions.current.col = 0;
		if (g_shell.positions.current.row >= g_shell.winsize.ws_row - 1)
		{
			tconf("sf");
			g_shell.positions.prompt.row--;
			g_shell.positions.cmd.row--;
		}
		else
			g_shell.positions.current.row++;
	}
	else
		g_shell.positions.current.col++;
	move_cursor(g_shell.positions.current.col, g_shell.positions.current.row);
}
