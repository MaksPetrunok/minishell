/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:40:01 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 17:26:56 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	win_size_handler(int __attribute__((unused)) sig)
{
	ioctl(0, TIOCGWINSZ, &(g_shell.winsize));
	if (!g_shell.canonical)
	{
		set_cursor(&(g_shell.positions.current));
		g_shell.positions.prompt.row = g_shell.positions.current.row -
			(g_shell.plen + g_shell.input->pos) / g_shell.winsize.ws_col;
		g_shell.positions.cmd.col = g_shell.plen % g_shell.winsize.ws_col;
		g_shell.positions.cmd.row = g_shell.positions.prompt.row +
			g_shell.plen / g_shell.winsize.ws_col;
	}
}

void	exit_safely(int __attribute__((unused)) sig)
{
	exit_shell();
	exit(1);
}

void	stp_handler(int __attribute__((unused)) sig)
{
	(void)sig;
}

void	sh_sigint_handler(int __attribute__((unused)) sig)
{
	if (sig == SIGSEGV)
	{
		exit_shell();
		ft_dprintf(2, "\n%s: unexpected error\n", SHELL_NAME);
		exit(1);
	}
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
	g_shell.inp_state = S_GEN;
	free((void *)(g_shell.const_input));
	g_shell.const_input = NULL;
	g_shell.history->iter = g_shell.history->stack;
	g_shell.run = 0;
	write(1, "\n", 1);
	if (finish_child_processes() == 0)
		show_prompt();
	g_shell.last_ret = 130;
}

void	setup_signals(void)
{
	signal(SIGINT, &sh_sigint_handler);
	signal(SIGTSTP, &stp_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, &exit_safely);
	signal(SIGHUP, &exit_safely);
	signal(SIGWINCH, &win_size_handler);
	signal(SIGSEGV, &sh_sigint_handler);
}
