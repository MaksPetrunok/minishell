/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:40:01 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/10 07:58:52 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_child;

void	win_size_handler(int UNUSED sig)
{
	ioctl(0, TIOCGWINSZ, &(shell.w));
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

void	sh_sig_handler(int UNUSED sig)
{
	shell.input->pos = 0;
	shell.input->len = 0;
	shell.input->data[0] = 0;
//	input_buff_free(&(shell.input));
	write(1, "\n", 1);
	if (g_child)
	{
		kill(g_child, SIGINT);
		g_child = 0;
	}
	else
	{
		show_prompt();
	}

}
