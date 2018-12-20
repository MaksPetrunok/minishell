/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:17:50 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/20 20:17:20 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	increase_buff(t_inp_buff *buff)
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

	if ((g_shell.plen + buff->len + 1) % g_shell.winsize.ws_col == 0)
	{
		tconf("ce"); //clear curent line from cursor to end
		tconf("do"); //move cursor down
		tconf("cr"); //return to begining of current line
		tconf("cd"); //clear curent line and to bottom
		i = 0;
		while (i++ < g_shell.cursor->col)
			tconf("nd"); //move cursor right
		tconf("up");
	}
	else
		tconf("ce"); //clear end of line
	i = buff->pos;
	while (buff->data[i])
	{
		ft_printf("%s", buff->data[i++]);
		tconf("le");
		cur_mv_right();
	}
	while (i-- > buff->pos)
		cur_mv_left();
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
