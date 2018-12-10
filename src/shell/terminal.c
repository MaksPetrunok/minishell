/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 19:57:56 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/10 01:31:05 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_parent_terminal(void)
{
	if ((shell.term_ref = malloc(sizeof(struct termios))) == NULL)
		return (-1);
	if (tcgetattr(0, shell.term_ref) != 0)
		return (-1);
	return (0);
}

int	set_working_terminal(void)
{
	char	*terminal_name;

	if ((shell.term_current = malloc(sizeof(struct termios))) == NULL)
		return (-1);
	if ((terminal_name = get_var("TERM")) != NULL &&
		*terminal_name != '\0')
		if (tgetent(0, terminal_name) != 1)
			ft_dprintf(2, "%s: can't find terminal definition for %s\n",
				SHELL_NAME, terminal_name);
	if (tcgetattr(0, shell.term_current) != 0)
		return (-1);
	shell.term_current->c_lflag &= ~(ECHO | ECHOE | ICANON);
	shell.term_current->c_cc[VMIN] = 1;
	shell.term_current->c_cc[VTIME] = 0;
	return (0);
}

int	switch_term_to(struct termios *term)
{
	if (tcsetattr(0, 0, term) != 0)
		return (-1);
	if (term == shell.term_ref)
		tconf("ei");
	else
		tconf("im");
	return (0);
}

int	setup_terminal(void)
{
	shell.term_ref = 0;
	shell.term_current = 0;
	if (set_parent_terminal() != 0 ||
		set_working_terminal() != 0)
	{
		free_terminals();
		return (-1);
	}
	return (0);
}

void free_terminals(void)
{
	free((void *)(shell.term_ref));
	free((void *)(shell.term_current));
}
