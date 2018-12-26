/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 16:45:00 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/26 19:05:17 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

int	history_add(char *cmd)
{
	t_dlist	*item;

	if ((item = malloc(sizeof(t_dlist))) == NULL)
		return (0);
	if ((item->str = ft_strdup(cmd)) == NULL)
	{
		free((void *)item);
		return (0);
	}
	free((void *)(g_shell.history->tmp));
	g_shell.history->tmp = NULL;
	item->prev = NULL;
	item->next = g_shell.history->stack;
	if (g_shell.history->stack)
		g_shell.history->stack->prev = item;
	g_shell.history->stack = item;
	g_shell.history->iter = item;
	return (1);
}

int	init_history(void)
{
	if ((g_shell.history = malloc(sizeof(t_history))) == NULL)
		return (-1);
	g_shell.history->stack = NULL;
	g_shell.history->iter = NULL;
	g_shell.history->tmp = NULL;
	return (0);
}
