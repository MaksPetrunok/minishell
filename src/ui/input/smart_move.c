/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 19:18:56 by mpetruno          #+#    #+#             */
/*   Updated: 2019/01/06 19:19:56 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

int	inp_movelw(t_inp_buff *buff, char *sym)
{
	(void)sym;
	if (buff->len == 0)
		return (0);
	while (buff->pos > 0 && !ft_isalnum(buff->data[buff->pos - 1][0]))
	{
		buff->pos--;
		cur_mv_left();
	}
	while (buff->pos > 0 && ft_isalnum(buff->data[buff->pos - 1][0]))
	{
		buff->pos--;
		cur_mv_left();
	}
	return (1);
}

int	inp_moverw(t_inp_buff *buff, char *sym)
{
	(void)sym;
	if (buff->len == 0)
		return (0);
	while (buff->data[buff->pos] && !ft_isalnum(buff->data[buff->pos][0]))
	{
		buff->pos++;
		cur_mv_right();
	}
	while (buff->data[buff->pos] && ft_isalnum(buff->data[buff->pos][0]))
	{
		buff->pos++;
		cur_mv_right();
	}
	return (1);
}

int	inp_home(t_inp_buff *buff, char *sym)
{
	(void)sym;
	buff->pos = 0;
	g_shell.positions.current.col = g_shell.positions.cmd.col;
	g_shell.positions.current.row = g_shell.positions.cmd.row;
	move_cursor(g_shell.positions.current.col, g_shell.positions.current.row);
	return (1);
}

int	inp_end(t_inp_buff *buff, char *sym)
{
	t_positions	*pos;

	(void)sym;
	pos = &(g_shell.positions);
	buff->pos = buff->len;
	pos->current.col = (pos->cmd.col + buff->len) % g_shell.winsize.ws_col;
	pos->current.row = pos->cmd.row +
		(pos->cmd.col + buff->len) / g_shell.winsize.ws_col;
	move_cursor(pos->current.col, pos->current.row);
	return (1);
}
