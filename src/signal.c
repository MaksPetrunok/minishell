/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:40:01 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/26 21:52:59 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

void	win_size_handler(int __attribute__((unused)) sig)
{
//	move_cursor(g_shell.positions.prompt.col, g_shell.positions.prompt.col);
//	write(1, "X", 1);

	/*
	int	i;

	if (g_shell.canonical)
		return ;
	while (g_shell.positions.current.row > 0)
		cur_mv_up();

	tconf("cr");
	tconf("cd");
	*/
	ioctl(0, TIOCGWINSZ, &(g_shell.winsize));
	/*
	show_prompt();
	i = 0;
	while (i < g_shell.input->len)
	{
		ft_putstr(g_shell.input->data[i++]);
		tconf("le");
		cur_mv_right();
	}
	while (i-- > g_shell.input->pos)
		cur_mv_left();
		*/
}

void	exit_safely(int __attribute__((unused)) sig)
{
	exit_shell();
	exit(1);
}

void	stp_handler(int __attribute__((unused)) sig)
{
	ft_printf("cursor:");
	ft_printf(" prompt  (%d, %d)\n", g_shell.positions.prompt.col, g_shell.positions.prompt.row);
	ft_printf("     cmd     (%d, %d)\n", g_shell.positions.cmd.col, g_shell.positions.cmd.row);
	ft_printf("     current (%d, %d)\n", g_shell.positions.current.col, g_shell.positions.current.row);
}

void	setup_signals(void)
{
	signal(SIGINT, &sh_sigint_handler);
	signal(SIGTSTP, &stp_handler); //
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, &exit_safely);
	signal(SIGHUP, &exit_safely);
	signal(SIGWINCH, &win_size_handler); // fix me!
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
	g_shell.history->iter = g_shell.history->stack;
	g_shell.run = 0;
	write(1, "\n", 1);
	if (finish_child_processes() == 0)
		show_prompt();
}
