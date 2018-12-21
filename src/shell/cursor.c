/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 19:58:48 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/21 16:59:59 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

void	cur_mv_up(void)
{
	if (g_shell.cursor->row > 0)
	{
		g_shell.cursor->row--;
		tconf("up");
	}
}

void	cur_mv_down(void)
{
	g_shell.cursor->row++;
	tconf("do");
}

void	cur_mv_left(void)
{
	int	i;

	if (g_shell.cursor->col == 0 && g_shell.cursor->row > 0)
	{
		g_shell.cursor->col = g_shell.winsize.ws_col - 1;
		g_shell.cursor->row--;
		i = g_shell.winsize.ws_col;
		while (i-- > 1)
			tconf("nd");
		tconf("up");
	}
	else
	{
		g_shell.cursor->col--;
		//tconf(tgoto(tgetstr("cm", 0), g_shell.cursor->col, g_shell.cursor->row));
		char    buf[32];
	    char    *pbuf;
	    void    *ret;

	    pbuf = buf;
	    ret = tgetstr("cm", &pbuf);
		if (ret == 0)
			ft_printf("tgetstr=0\n");
	    pbuf = tgoto(buf, 0, 0);
		if (pbuf == 0)
			ft_printf("tgoto=0\n");
	    techo(pbuf);
		tconf("vb");
		sleep(1);
		while (*pbuf)
			ft_printf("\n%d", *pbuf++);
		//tconf(tgoto(tgetstr("cm", 0), 1, 1));
//		tconf("le");
	}
}

void	cur_mv_right(void)
{
	if (g_shell.cursor->col >= g_shell.winsize.ws_col - 1)
	{
		g_shell.cursor->col = 0;
		g_shell.cursor->row++;
//		tconf("do");
		tconf("sf");
//		tconf("cr");
	}
	else
	{
		g_shell.cursor->col++;
		tconf("nd");
	}
}

int	init_cursor(void)
{
	if ((g_shell.cursor = malloc(sizeof(t_cursor))) == 0)
		return (-1);
	g_shell.cursor->col = 0;
	g_shell.cursor->row = 0;
	return (0);
}
