/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:17:50 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/26 20:46:50 by mpetruno         ###   ########.fr       */
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
	if ((g_shell.positions.current.col + buff->len - buff->pos) %
		g_shell.winsize.ws_col == 0)
	{
		g_shell.positions.prompt.row--;
		g_shell.positions.cmd.row--;
		g_shell.positions.current.row--;
	}
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
	if (buff->pos == buff->len)
	{
		ft_putstr(buff->data[buff->pos]);
		tconf("le");
	}
	else
		refresh_ui(buff);
	cur_mv_right();
	buff->pos++;
	buff->len++;
	return (1);
}
