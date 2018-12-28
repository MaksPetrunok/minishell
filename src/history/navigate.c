/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 16:49:46 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/28 15:17:20 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_down(t_inp_buff *buff)
{
//check if it's last row
	if (g_shell.positions.cmd.col + buff->len > g_shell.winsize.ws_col - 1)
	{
		move_cursor(0, g_shell.positions.cmd.row + 1);
		tconf("cd");
	}
	move_cursor(g_shell.positions.cmd.col, g_shell.positions.cmd.row);
	tconf("ce");
	g_shell.positions.current.col = g_shell.positions.cmd.col;
	g_shell.positions.current.row = g_shell.positions.cmd.row;
}

static void	free_buff_data(t_inp_buff *buff)
{
	int	i;

	i = 0;
	while (buff->data[i])
		free((void *)(buff->data[i++]));
	buff->pos = 0;
	buff->len = 0;
	buff->data[0] = NULL;
}


static int	update_input(t_inp_buff *buff, char *str)
{
	char	sym[2];

	clean_down(buff);
	free_buff_data(buff);
	sym[1] = '\0';
	while (*str)
	{
		*sym = *str++;
		inp_insert(buff, sym);
	}
	return (1);
}

int	inp_hist_prev(t_inp_buff *buff, char *sym)
{
	(void)sym;
	if (g_shell.history->stack == NULL)
		return (0);
	if (g_shell.history->tmp && g_shell.history->iter->next == NULL)
		return (0);
	if (g_shell.history->tmp == NULL)
	{
		if ((g_shell.history->tmp = inp_to_str(buff->data)) == NULL)
		{
			ft_dprintf(2, "history: allocation error");
			return (0);
		}
		g_shell.history->iter = g_shell.history->stack;
	}
	else if (g_shell.history->iter->next)
		g_shell.history->iter = g_shell.history->iter->next;
	else
		return (0);
	update_input(buff, g_shell.history->iter->str);
	return (1);
}

int	inp_hist_next(t_inp_buff *buff, char *sym)
{
	(void)sym;
	if (g_shell.history->stack == NULL || g_shell.history->tmp == NULL)
		return (0);
	if (g_shell.history->iter->prev == NULL)
	{
		update_input(buff, g_shell.history->tmp);
		free((void *)(g_shell.history->tmp));
		g_shell.history->tmp = NULL;
		return (1);
	}
	g_shell.history->iter = g_shell.history->iter->prev;
	update_input(buff, g_shell.history->iter->str);
	return (1);
}
