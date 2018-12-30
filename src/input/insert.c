/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:17:50 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/28 20:45:45 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	increase_buff(t_inp_buff *buff)
{
	int		new_size;
	size_t	new_bytes;
	size_t	old_bytes;
	char	**new_data;

	new_size = buff->size + INP_BUFF_SIZE;
	old_bytes = buff->size * sizeof(char **);
	new_bytes = new_size * sizeof(char **);
	new_data = ft_realloc((void *)(buff->data), old_bytes, new_bytes);
	if (new_data == buff->data || new_data == NULL)
		return (0);
	buff->data = new_data;
	buff->size = new_size;
	return (1);
}

static void	refresh_ui(t_inp_buff *buff)
{
	int	i;

	clear_from_cursor(buff);
	i = buff->pos;
	while (buff->data[i])
		ft_putstr(buff->data[i++]);
	ft_putstr(" ");
	tconf("le");
	if ((g_shell.positions.current.col + buff->len - buff->pos + 1) %
		g_shell.winsize.ws_col == 0)
	{
		g_shell.positions.current.col = 0;
		if (g_shell.positions.current.row == g_shell.winsize.ws_row - 1)
		{
			g_shell.positions.prompt.row--;
			g_shell.positions.cmd.row--;
		}
		else
			g_shell.positions.current.row++;
	}
	else
		g_shell.positions.current.col++;
	move_cursor(g_shell.positions.current.col, g_shell.positions.current.row);
}

int			inp_insert(t_inp_buff *buff, char *sym)
{
	int	i;

	if (buff->len >= buff->size - 1)
		if (!increase_buff(buff))
		{
			ft_dprintf(2, "\nfailed to increase input buffer\n");
			return (0);
		}
	i = buff->len;
	while (i >= buff->pos)
	{
		buff->data[i + 1] = buff->data[i];
		i--;
	}
	if ((buff->data[buff->pos] = ft_strdup(sym)) == NULL)
		return (0);
	refresh_ui(buff);
	buff->pos++;
	buff->len++;
	return (1);
}
/*
 * count rows required for prompt + new inp_buff and compare with position
 * of positions.promopt from bottom. If prompt position is less than number of
 * rows required for input - scroll up for N lines as required to adjust
 * prompt position.
 * Print prompt and input.
 * Set cursor positions (prompt, cmd, current).
 */
static void refresh(t_inp_buff *buff, int ins_len)
{
	t_cursor	cursor;
	int			i;
	
	clear_from_cursor(buff);
	i = buff->pos;
	while (buff->data[i])
		ft_putstr(buff->data[i++]);
	if ((g_shell.plen + buff->len + ins_len) % g_shell.winsize.ws_col == 0)
	{
		ft_putstr(" ");
		tconf("le");
	}
	set_cursor(&(cursor));
	if (g_shell.positions.prompt.row + (g_shell.plen + buff->len + ins_len) /
		g_shell.winsize.ws_col > g_shell.winsize.ws_row - 1)
		g_shell.positions.prompt.row = g_shell.winsize.ws_row - 1 - 
			(g_shell.plen + buff->len + ins_len) / g_shell.winsize.ws_col;
	g_shell.positions.cmd.col = g_shell.plen % g_shell.winsize.ws_col;
	g_shell.positions.cmd.row = g_shell.positions.prompt.row +
		g_shell.plen / g_shell.winsize.ws_col;
	g_shell.positions.current.col = (g_shell.plen + buff->pos + ins_len) %
		g_shell.winsize.ws_col;
	g_shell.positions.current.row = g_shell.positions.cmd.row +
		(g_shell.plen + buff->pos + ins_len) / g_shell.winsize.ws_col;
	move_cursor(g_shell.positions.current.col, g_shell.positions.current.row);
}

int			inp_insert_clipboard(t_inp_buff *buff)
{
	int		i;
	int		len;
	char	sym[2];

	if (g_shell.clipboard == NULL)
		return (0);
	len = ft_strlen(g_shell.clipboard);
	while (buff->len + len >= buff->size)
		if (!increase_buff(buff))
		{
			ft_dprintf(2, "\nfailed to increase input buffer\n");
			return (0);
		}
	i = buff->len;
	while (i >= buff->pos)
	{
		buff->data[i + len] = buff->data[i];
		i--;
	}
	i = 0;
	sym[1] = '\0';
	while (g_shell.clipboard[i])
	{
		*sym = g_shell.clipboard[i];
		if ((buff->data[buff->pos + i++] = ft_strdup(sym)) == NULL)
			return (0);
	}
	refresh(buff, len);
	buff->pos += len;
	buff->len += len;
	return (1);
}
