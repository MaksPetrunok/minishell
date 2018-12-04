/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:40:01 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/04 19:48:49 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_child;

void	setup_signals(void)
{
	signal(SIGINT, &sh_sig_handler);
}

void	sh_sig_handler(int UNUSED sig)
{
	if (g_child)
	{
		kill(g_child, SIGINT);
		g_child = 0;
		write(1, "\n", 1);
	}
	else
	{
		write(1, "\n", 1);
		show_prompt();
	}
}
