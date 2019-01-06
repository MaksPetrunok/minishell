/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 19:03:43 by mpetruno          #+#    #+#             */
/*   Updated: 2019/01/06 19:10:05 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

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
