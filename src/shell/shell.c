/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 20:10:49 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/10 07:18:43 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	shell;

static void	free_child_list(void)
{
	t_list	*tmp;

	while (shell.childs)
	{
		tmp = shell.childs->next;
		free((void *)shell.childs->content);
		free((void *)shell.childs);
		shell.childs = tmp;
	}
}

int	init_shell(char **env)
{
	shell.childs = NULL;
	shell.input = NULL;
	if ((shell.environ = init_environment(env)) == 0)
		return (-1);
	if (setup_terminal() != 0)
	{
		env_free(shell.environ);
		return (-1);
	}
	if (init_cursor() != 0)
	{
		exit_shell();
		return (-1);
	}
	if (ioctl(0, TIOCGWINSZ, &(shell.w)) == -1)
		return (-1);
//	ft_printf("rows: %d, cols: %d\n", shell.w.ws_row, shell.w.ws_col);
	setup_signals();
	switch_term_to(shell.term_current);
	return (0);
}

void	exit_shell(void)
{
	finish_child_processes();
	if (switch_term_to(shell.term_ref) == -1)
		ft_dprintf(2, "%s: unable restore terminal settings\n", SHELL_NAME);
	free_child_list();
	free_terminals();
	env_free(shell.environ);
	free((void *)(shell.cursor));
}
