/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:13:49 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/28 20:45:47 by mpetruno         ###   ########.fr       */
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

	{K_CTRL_A, &inp_copy_all},
	{K_CTRL_X, &inp_cut_all},
	{K_CTRL_P, &inp_paste},
	{K_CTRL_U, &inp_cut_backward},
	{K_CTRL_K, &inp_cut_forward},
	{K_CTRL_B, &inp_copy_backward},
	{K_CTRL_F, &inp_copy_forward},
	{NULL, &inp_ignore}
};

int	inp_copy_all(t_inp_buff *buff, char *sym)
{
	(void)sym;
	free((void *)(g_shell.clipboard));
	g_shell.clipboard = inp_to_str(buff->data);
	return (0);
}
int	inp_cut_all(t_inp_buff *buff, char *sym)
{
	int	i;

	inp_copy_all(buff, sym);
	inp_home(buff, sym);
	clear_from_cursor(buff);
	i = 0;
	while (buff->data[i])
		free((void *)(buff->data[i++]));
	buff->data[0] = NULL;
	buff->pos = 0;
	buff->len = 0;
	return (0);
}
int	inp_paste(t_inp_buff *buff, char *sym)
{
	(void)sym;
	inp_insert_clipboard(buff);
	return (0);
}
int	inp_cut_backward(t_inp_buff *buff, char *sym)
{
	int	i;
	int	pos;

	inp_copy_backward(buff, sym);
	clear_from_cursor(buff);
	g_shell.positions.current.col = g_shell.positions.cmd.col;
	g_shell.positions.current.row = g_shell.positions.cmd.row;
	move_cursor(g_shell.positions.cmd.col,
				g_shell.positions.cmd.row);
	clear_from_cursor(buff);
	i = 0;
	while (i < buff->pos)
		free((void *)(buff->data[i++]));
	i = 0;
	pos = buff->pos;
	while (pos <= buff->len)
		buff->data[i++] = buff->data[pos++];
	buff->len -= buff->pos;
	buff->pos = 0;
	i = 0;
	while (buff->data[i])
		ft_putstr(buff->data[i++]);
	move_cursor(g_shell.positions.current.col,
				g_shell.positions.current.row);
	return (0);
}
int	inp_cut_forward(t_inp_buff *buff, char *sym)
{
	int	i;

	inp_copy_forward(buff, sym);
	clear_from_cursor(buff);
	i = buff->pos;
	while (i < buff->len)
		free((void *)(buff->data[i++]));
	buff->data[buff->pos] = NULL;
	buff->len = buff->pos;
	return (0);
}
int	inp_copy_backward(t_inp_buff *buff, char *sym)
{
	char	*tmp;

	(void)sym;
	tmp = buff->data[buff->pos];
	buff->data[buff->pos] = NULL;
	inp_copy_all(buff, 0);
	buff->data[buff->pos] = tmp;
	return (0);
}
int	inp_copy_forward(t_inp_buff *buff, char *sym)
{
	(void)sym;
	free((void *)(g_shell.clipboard));
	g_shell.clipboard = inp_to_str(buff->data + buff->pos);
	return (0);
}
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
