/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 20:45:34 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/26 20:54:14 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_from_cursor(t_inp_buff *buff)
{
	if (g_shell.positions.current.col + buff->len - buff->pos >
		g_shell.winsize.ws_col - 1)
	{
		if (g_shell.positions.current.row < g_shell.winsize.ws_row - 1)
		{
			move_cursor(0, g_shell.positions.current.row + 1);
			tconf("cd");
			move_cursor(g_shell.positions.current.col,
						g_shell.positions.current.row);
		}
	}
	tconf("ce");
}
