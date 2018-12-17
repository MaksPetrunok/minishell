/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:40:01 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/12 21:46:15 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

void	win_size_handler(int UNUSED sig)
{
	ioctl(0, TIOCGWINSZ, &(g_shell.w));
}

void	exit_safely(int UNUSED sig)
{
	exit_shell();
	exit(1);
}

void	setup_signals(void)
{
	signal(SIGINT, &sh_sig_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, &exit_safely);
	signal(SIGHUP, &exit_safely);
	signal(SIGWINCH, &win_size_handler);
}
// make it handler for SIGINT
void	sh_sig_handler(int UNUSED sig)
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
