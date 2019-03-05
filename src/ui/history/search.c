/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 16:45:00 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/18 11:10:03 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*search_prev(const char *pattern)
{
	while (g_shell.history->iter && *pattern)
	{
		if (ft_strstr(g_shell.history->iter->str, pattern) != NULL)
			return (g_shell.history->iter->str);
		g_shell.history->iter = g_shell.history->iter->next;
	}
	return (NULL);
}

static void	reset_search(void)
{
	int	i;

	i = 0;
	while (i < 1024)
		g_shell.srch_req[i++] = '\0';
	g_shell.isearch = 1;
	g_shell.history->iter = g_shell.history->stack;
}

int	inp_isearch(t_inp_buff *buff, char *sym)
{
	char		*result;

	if (g_shell.isearch == 0 && *sym == 0x12)
		reset_search();
	else if (g_shell.isearch && *sym == 0x12 && g_shell.history->iter != NULL)
		g_shell.history->iter = g_shell.history->iter->next;
	else if (g_shell.isearch && *sym == 0x7f)
		g_shell.srch_req[ft_strlen(g_shell.srch_req) - 1] = '\0';
	else if (g_shell.isearch && *sym != 0x12 &&
		ft_strlen(g_shell.srch_req) < 1020)
		g_shell.srch_req[ft_strlen(g_shell.srch_req)] = *sym;
	result = search_prev(g_shell.srch_req);
	if (result != NULL)
		update_input(buff, result);
	show_prompt();
	return (1);
}

