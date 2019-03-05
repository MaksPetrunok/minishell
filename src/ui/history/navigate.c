/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 16:49:46 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/18 12:41:13 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int			update_input(t_inp_buff *buff, char *str)
{
	char	sym[2];
	int		isearch;

	isearch = g_shell.isearch;
	g_shell.isearch = 0;
	move_cursor(0, g_shell.positions.prompt.row);
	tconf("cd");
	show_prompt();
	free_buff_data(buff);
	sym[1] = '\0';
	while (*str)
	{
		*sym = *str++;
		inp_insert(buff, sym);
	}
	g_shell.isearch = isearch;
	return (1);
}

int			inp_hist_prev(t_inp_buff *buff, char *sym)
{
	(void)sym;
	g_shell.isearch = 0;
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

int			inp_hist_next(t_inp_buff *buff, char *sym)
{
	(void)sym;
	g_shell.isearch = 0;
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
