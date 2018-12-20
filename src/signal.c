/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:40:01 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/18 14:29:29 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

void	win_size_handler(int __attribute__((unused)) sig)
{
	int	position;

	ioctl(0, TIOCGWINSZ, &(g_shell.winsize));
	position = g_shell.plen + g_shell.input->pos;
	g_shell.cursor->col = position % g_shell.winsize.ws_col;
	g_shell.cursor->row = position / g_shell.winsize.ws_col;
//ft_printf("col=%d, row=%d", g_shell.cursor->col, g_shell.cursor->row);
}

void	exit_safely(int __attribute__((unused)) sig)
{
	exit_shell();
	exit(1);
}

void	setup_signals(void)
{
	signal(SIGINT, &sh_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, &exit_safely);
	signal(SIGHUP, &exit_safely);
	signal(SIGWINCH, &win_size_handler);
}

void	sh_sigint_handler(int __attribute__((unused)) sig)
{
	if (g_shell.input != NULL)
	{
		while (g_shell.input->len >= 0)
		{
			free((void *)(g_shell.input->data[g_shell.input->len--]));
		}
		g_shell.input->pos = 0;
		g_shell.input->len = 0;
		g_shell.input->data[0] = NULL;
	}
	g_shell.run = 0;
	write(1, "\n", 1);
	if (finish_child_processes() == 0)
		show_prompt();
}
