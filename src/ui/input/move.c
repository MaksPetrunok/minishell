/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:17:38 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/18 11:10:48 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	inp_movel(t_inp_buff *buff, char *sym)
{
	(void)sym;
	if (buff->pos == 0)
		return (0);
	buff->pos--;
	cur_mv_left();
	return (1);
}

int	inp_mover(t_inp_buff *buff, char *sym)
{
	(void)sym;
	if (buff->pos == buff->len)
		return (0);
	cur_mv_right();
	buff->pos++;
	return (1);
}

int	inp_up(t_inp_buff *buff, char *sym)
{
	t_positions	*pos;

	(void)sym;
	pos = &(g_shell.positions);
	if (pos->current.row == pos->cmd.row)
		return (0);
	if (pos->current.col < pos->cmd.col &&
		pos->current.row - pos->cmd.row == 1)
	{
		buff->pos = 0;
		pos->current.col = pos->cmd.col;
		pos->current.row = pos->cmd.row;
	}
	else
	{
		buff->pos -= g_shell.winsize.ws_col;
		pos->current.row--;
	}
	move_cursor(pos->current.col, pos->current.row);
	return (1);
}

int	inp_down(t_inp_buff *buff, char *sym)
{
	t_positions	*pos;

	(void)sym;
	pos = &(g_shell.positions);
	if (pos->current.col + buff->len - buff->pos < g_shell.winsize.ws_col)
		return (0);
	if (buff->len - buff->pos < g_shell.winsize.ws_col)
	{
		pos->current.col = (pos->current.col + buff->len - buff->pos) %
			g_shell.winsize.ws_col;
		buff->pos = buff->len;
	}
	else
		buff->pos += g_shell.winsize.ws_col;
	pos->current.row++;
	move_cursor(pos->current.col, pos->current.row);
	return (1);
}
