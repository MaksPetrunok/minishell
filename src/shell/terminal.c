/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 19:57:56 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/11 22:54:03 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	initialize(void)
{
	shell.term_default = malloc(sizeof(struct termios));
	shell.term_typing = malloc(sizeof(struct termios));
	if (shell.term_default == NULL || shell.term_typing == NULL)
		return (-1);
	if (tcgetattr(0, shell.term_default) != 0)
		return (-1);
	ft_memcpy((void *)shell.term_typing, (void *)shell.term_default,
		sizeof(struct termios));
	shell.term_typing->c_lflag &= ~(ECHO | ECHOE | ICANON);
	shell.term_typing->c_cc[VMIN] = 1;
	shell.term_typing->c_cc[VTIME] = 0;
	return (0);
}

static int	set_terminal_db(void)
{
	char	*name;

	name = get_var("TERM");
	if (name == NULL || *name == '\0')
		return (0);
	return (tgetent(0, name));
}

int	switch_term_to(struct termios *term)
{
	if (term == shell.term_typing)
	{
		if (set_terminal_db())
		{
			if (tcsetattr(0, 0, term) != 0)
				return (-1);
			shell.canonical = 0;
			return (0);
		}
	}
	if (tcsetattr(0, 0, shell.term_default) != 0)
		return (-1);
	shell.canonical = 1;
	return (0);
}

int	setup_terminal(void)
{
	shell.term_default = 0;
	shell.term_typing = 0;
	if (initialize() != 0)
	{
		free_terminals();
		return (-1);
	}
	return (0);
}

void free_terminals(void)
{
	free((void *)(shell.term_default));
	free((void *)(shell.term_typing));
}
