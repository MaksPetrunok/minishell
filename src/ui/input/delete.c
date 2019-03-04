/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:17:24 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/18 11:10:30 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	refresh_inp(t_inp_buff *buff)
{
	int	i;

	tconf("ce");
	if (g_shell.positions.current.col + (buff->len - buff->pos) >=
		g_shell.winsize.ws_col - 1)
	{
		move_cursor(0, g_shell.positions.current.row + 1);
		tconf("cd");
		move_cursor(g_shell.positions.current.col,
					g_shell.positions.current.row);
	}
	i = buff->pos;
	while (buff->data[i])
		ft_putstr(buff->data[i++]);
	move_cursor(g_shell.positions.current.col,
				g_shell.positions.current.row);
}

int			inp_backsp(t_inp_buff *buff, char *sym)
{
	(void)sym;
	if (buff->pos == 0)
		return (1);
	buff->pos--;
	cur_mv_left();
	inp_delete(buff, sym);
	return (1);
}

int			inp_delete(t_inp_buff *buff, char *sym)
{
	int	i;

	(void)sym;
	if (buff->pos == buff->len)
		return (1);
	free((void *)(buff->data[buff->pos]));
	i = buff->pos;
	while (i < buff->len)
	{
		buff->data[i] = buff->data[i + 1];
		i++;
	}
	buff->len--;
	refresh_inp(buff);
	return (1);
}
