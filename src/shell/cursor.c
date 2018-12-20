/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 19:58:48 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/20 18:48:29 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

void	cur_mv_left(void)
{
	int	i;

	if (g_shell.cursor->col == 0 && g_shell.cursor->row > 0)
	{
		g_shell.cursor->col = g_shell.winsize.ws_col - 1;
		g_shell.cursor->row--;
		i = g_shell.winsize.ws_col;
		while (i-- > 1)
			tconf("nd");
		tconf("up");
//		tconf("vb"); //
	}
	else
	{
		g_shell.cursor->col--;
		tconf("le");
	}
}

void	cur_mv_right(int __attribute__((unused)) insert)
{
	if (g_shell.cursor->col >= g_shell.winsize.ws_col - 1) // - insert)
	{
		g_shell.cursor->col = 0;
		g_shell.cursor->row++;
		tconf("do");
		tconf("cr");
//		tconf("vb"); //
	}
	else
	{
		g_shell.cursor->col++;
//		if (!insert)
			tconf("nd");
	}
}

int	init_cursor(void)
{
	if ((g_shell.cursor = malloc(sizeof(t_cursor))) == 0)
		return (-1);
	g_shell.cursor->col = 0;
	g_shell.cursor->row = 0;
	return (0);
}
