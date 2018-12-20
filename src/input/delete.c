/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:17:24 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/20 20:17:01 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static void	refresh_ui(t_inp_buff *buff)
{
	int	i;

	tconf("ce"); //clear curent line from cursor to end
	if (g_shell.cursor->col + buff->len - buff->pos >= g_shell.winsize.ws_col - 1)
	{
		tconf("do"); //move cursor down
		tconf("cr"); //return to begining of current line
		tconf("cd"); //clear curent line and to bottom
		i = 0;
		while (i++ < g_shell.cursor->col)
			tconf("nd"); //move cursor right
		tconf("up");
	}
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
int	inp_backsp(t_inp_buff *buff, char *sym)
{
	(void)sym;
	if (buff->pos == 0)
		return (0);
	buff->pos--;
	cur_mv_left();
	inp_delete(buff, sym);
	return (1);
}

int	inp_delete(t_inp_buff *buff, char *sym)
{
	int	i;

	(void)sym;
	if (buff->pos == buff->len)
		return (0);
//	tconf("dc");
	
	free((void *)(buff->data[buff->pos]));
	i = buff->pos;
	while (i < buff->len)
	{
		buff->data[i] = buff->data[i + 1];
		i++;
	}
	buff->len--;
	refresh_ui(buff);
	return (1);
}
