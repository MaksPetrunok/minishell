/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 11:52:22 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/06 22:40:04 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_term_ref(void)
{
	char	*terminal_name;

	if ((terminal_name = get_var("TERM")) == NULL ||
		*terminal_name == '\0')
		return (-1);
	if ((shell.term_ref = malloc(sizeof(struct termios))) == NULL)
		return (-1);
	if (tgetent(0, terminal_name) != 1 ||
		(tcgetattr(0, shell.term_ref) != 0))
	{
		free((void *)shell.term_ref);
		shell.term_ref = NULL;
		return (-1);
	}
	return (0);
}

int	configure_term(void)
{
	if (shell.term_ref == NULL ||
		(shell.term_current = malloc(sizeof(struct termios))) == NULL)
		return (-1);
	ft_memcpy(shell.term_current, shell.term_ref, sizeof(struct termios));
	shell.term_current->c_lflag &= ~(ECHO | ECHOE | ICANON);
	shell.term_current->c_cc[VMIN] = 1;
	shell.term_current->c_cc[VTIME] = 0;
	if (tcsetattr(0, 0, shell.term_current) != 0)
		return (-1);
	tconf("im");
	return (0);
}

int	init_cursor(void)
{
	if ((shell.cursor = malloc(sizeof(t_cursor))) == 0)
		return (-1);
	shell.cursor->col = 0;
	shell.cursor->row = 0;
	return (0);
}
