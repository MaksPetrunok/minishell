/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 13:18:53 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/18 13:19:16 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*qprompt[4] =
{
	[S_SQT] = "quote> ",
	[S_DQT] = "dquote> ",
	[S_BQT] = "bquote> "
};

static int	print_prompt()
{
	char	*tmp;
	char	cwd[5000];
	char	*is_wd;

	cwd[0] = '\0';
	is_wd = getcwd(cwd, 5000);
	if (g_shell.inp_state != S_GEN && g_shell.inp_state != S_HSH)
		return (ft_printf("%s", qprompt[g_shell.inp_state]));
	else if ((tmp = get_var("HOME", g_shell.environ)) == 0 || *tmp == '\0')
	{
		if (!is_wd)
			return (ft_printf("%s: ", SHELL_NAME));
		else
			return (ft_printf("\x1b[1m%s:\x1b[0;94m%s\x1b[0m$ ",
				SHELL_NAME, cwd) - 15);
	}
	else if (ft_strstr(cwd, tmp) == cwd)
		return (ft_printf("\x1b[1m%s:\x1b[94m~%s\x1b[0m$ ",
			SHELL_NAME, cwd + ft_strlen(tmp)) - 13);
	else
		return (ft_printf("\x1b[1m%s:\x1b[94m%s\x1b[0m$ ",
			SHELL_NAME, cwd) - 13);
}

void	show_prompt(void)
{
	int		len;

	switch_term_to(g_shell.term_typing);
	set_cursor(&(g_shell.positions.prompt));
	tconf("cd");
	len = print_prompt();
	g_shell.plen = len;
	g_shell.positions.cmd.col = len % g_shell.winsize.ws_col;
	g_shell.positions.cmd.row = g_shell.positions.prompt.row +
		len / g_shell.winsize.ws_col;
	g_shell.positions.current.col = g_shell.positions.cmd.col;
	g_shell.positions.current.row = g_shell.positions.cmd.row;
}
