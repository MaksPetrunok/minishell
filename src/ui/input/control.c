/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:13:49 by mpetruno          #+#    #+#             */
/*   Updated: 2019/01/06 20:49:20 by mpetruno         ###   ########.fr       */
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
	{K_CTRL_D, &inp_eof},

	{K_CTRL_A, &inp_copy_all},
	{K_CTRL_X, &inp_cut_all},
	{K_CTRL_P, &inp_paste},
	{K_CTRL_U, &inp_cut_backward},
	{K_CTRL_K, &inp_cut_forward},
	{K_CTRL_B, &inp_copy_backward},
	{K_CTRL_F, &inp_copy_forward},
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

int	inp_control(t_inp_buff *buff, char *sym)
{
	int	i;

	i = 0;
	while (g_table[i].code && ft_strcmp(g_table[i].code, sym))
		i++;
	return (g_table[i].action(buff, sym));
}

int	inp_tab(t_inp_buff *buff, char *sym)
{
	(void)sym;
	if (buff->pos == buff->len)
		auto_complete(buff);
	return (1);
}

int	inp_ignore(t_inp_buff *buff, char *sym)
{
	(void)buff;
	(void)sym;
	return (1);
}
