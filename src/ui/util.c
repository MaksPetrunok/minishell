/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 17:42:37 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/18 11:11:38 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
