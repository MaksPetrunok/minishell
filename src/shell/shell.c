/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 20:10:49 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/12 15:30:59 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

static void	free_child_list(void)
{
	t_list	*tmp;

	while (g_shell.childs)
	{
		tmp = g_shell.childs->next;
		free((void *)g_shell.childs->content);
		free((void *)g_shell.childs);
		g_shell.childs = tmp;
	}
}

int	init_shell(char **env)
{
	g_shell.childs = NULL;
	g_shell.input = NULL;
	g_shell.last_ret = 0;
	if ((g_shell.environ = init_environment(env)) == 0)
		return (-1);
	if (setup_terminal() != 0)
	{
		env_free(g_shell.environ);
		return (-1);
	}
//	if (init_cursor() != 0)
//	{
//		exit_g_shell.);
//		return (-1);
//	}

//	if (ioctl(0, TIOCGWINSZ, &(g_shell.w)) == -1)
//		return (-1);
//	ft_printf("rows: %d, cols: %d\n", g_shell.w.ws_row, g_shell.w.ws_col);
	setup_signals();
	return (0);
}

void	exit_shell(void)
{
	finish_child_processes();
	if (switch_term_to(g_shell.term_default) == -1)
		ft_dprintf(2, "%s: unable restore terminal settings\n", SHELL_NAME);
	free_child_list();
	free_terminals();
	env_free(g_shell.environ);
	free((void *)(g_shell.cursor));
}
