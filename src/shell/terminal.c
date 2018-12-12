/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 19:57:56 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/12 21:55:54 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

static int	initialize(void)
{
	g_shell.term_default = malloc(sizeof(struct termios));
	g_shell.term_typing = malloc(sizeof(struct termios));
	if (g_shell.term_default == NULL || g_shell.term_typing == NULL)
		return (-1);
	if (tcgetattr(0, g_shell.term_default) != 0)
		return (-1);
	ft_memcpy((void *)g_shell.term_typing, (void *)g_shell.term_default,
		sizeof(struct termios));
	g_shell.term_typing->c_lflag &= ~(ECHO | ECHOE | ICANON);
	g_shell.term_typing->c_cc[VMIN] = 1;
	g_shell.term_typing->c_cc[VTIME] = 0;
	return (0);
}

static int	set_terminal_db(void)
{
	static char	*last_db = NULL;
	char		*name;

	name = get_var("TERM");
	if (name == 0 || tgetent(0, name) != 1)
	{
		if (last_db != name)
		{
			if (name == NULL || *name == '\0')
				ft_dprintf(2,
					"terminal not specified, use: setenv TERM <term-name>\n");
			else
				ft_dprintf(2,
					"terminal database '%s' not found\n", name);
			last_db = name;
		}
		return (0);
	}
	last_db = name;
	return (1);
}

int	switch_term_to(struct termios *term)
{
	if (term == g_shell.term_typing)
	{
		if (set_terminal_db())
		{
			if (tcsetattr(0, 0, term) != 0)
				return (-1);
			g_shell.canonical = 0;
			return (0);
		}
	}
	if (tcsetattr(0, 0, g_shell.term_default) != 0)
		return (-1);
	g_shell.canonical = 1;
	return (0);
}

int	setup_terminal(void)
{
	g_shell.term_default = 0;
	g_shell.term_typing = 0;
	if (initialize() != 0)
	{
		free_terminals();
		return (-1);
	}
	return (0);
}

void free_terminals(void)
{
	free((void *)(g_shell.term_default));
	free((void *)(g_shell.term_typing));
}
