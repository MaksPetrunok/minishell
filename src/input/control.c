/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:13:49 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/26 16:30:35 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_key	g_table[KEY_NUM] = {
	{K_LEFT, &inp_movel},
	{K_RIGHT, &inp_mover},
	{K_SH_LEFT, &inp_movelw},
	{K_SH_RIGHT, &inp_moverw},
	{K_UP, &inp_hist_prev},
	{K_DOWN, &inp_hist_next},
	{K_BACK_SP, &inp_backsp},
	{K_DEL, &inp_delete},
	{K_TAB, &inp_tab},
	{K_SH_HOME, &inp_home},
	{K_SH_END, &inp_end},
	{K_SH_PGUP, &inp_up},
	{K_SH_PGDOWN, &inp_down},
	{NULL, &inp_ignore}
};

int	is_control(char *str)
{
	int	i;

	i = 0;
	while (g_table[i].code)
		if (ft_strstr(g_table[i].code, str) == g_table[i].code)
		{
			if (ft_strequ(g_table[i].code, str))
				return (2);
			else
				return (1);
		}
		else
			i++;
	return (0);
}

int	inp_tab(t_inp_buff *buff, char *sym)
{
	int	i;

	i = buff->pos;
	while (i >= 0)
	{
		if (buff->data[i] &&
			buff->data[i][0] != ' ' &&
			buff->data[i][0] != '\t')
		{
			auto_complete(buff);
			return (1);
		}
		i--;
	}
	inp_insert(buff, sym);
	return (1);
}

int	inp_control(t_inp_buff *buff, char *sym)
{
	int	i;

	i = 0;
	while (g_table[i].code && ft_strcmp(g_table[i].code, sym))
		i++;
	return (g_table[i].action(buff, sym));
}

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

int	inp_up(t_inp_buff *buff, char *sym)
{
	t_positions	*pos;

	(void)sym;
	pos = &(g_shell.positions);
	if (pos->current.row == pos->cmd.row)
		return (0);
	if (pos->current.col < pos->cmd.col)
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
