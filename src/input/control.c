/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:13:49 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/21 15:49:12 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_key	g_table[KEY_NUM] = {
	{K_LEFT, &inp_movel},
	{K_RIGHT, &inp_mover},
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

int	inp_home(t_inp_buff *buff, char *sym)
{
	while (buff->pos > 0)
	{
		inp_movel(buff, sym);
	}
	return (1);
}

int	inp_end(t_inp_buff *buff, char *sym)
{
	while (buff->pos < buff->len)
	{
		inp_mover(buff, sym);
	}
	return (1);
}

int	inp_up(t_inp_buff *buff, char *sym)
{
	(void)sym;
	if (g_shell.cursor->col == 0)
		return (0);
	buff->pos = buff->pos - g_shell.cursor->col;
	if (buff->pos < 0)
		buff->pos = 0;
	if (buff->pos != 0)
		cur_mv_up();
	else
	{
		while (g_shell.cursor->col != g_shell.plen)
			cur_mv_left();
	}
	return (1);
}

int	inp_down(t_inp_buff *buff, char *sym)
{
//	tconf(tgoto(tgetstr("cm", NULL), x, y));
	if (g_shell.cursor->col + buff->len - buff->pos < g_shell.winsize.ws_col)
		return (0);
	if (buff->pos + g_shell.winsize.ws_col > buff->len)
	{
		while (buff->pos < buff->len)
			inp_mover(buff, sym);
	}
	else
	{
		buff->pos += g_shell.winsize.ws_col;
		cur_mv_down();
	}
	return (1);
}
