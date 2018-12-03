/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 16:19:27 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/03 18:06:16 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	putch(int c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	write(2, &ch, 1);
	return (0);
}

int	init_keyboard()
{
	struct termios	term;
	char			*buff;

	if (tgetent(0, get_var("TERM")) != 1)
		return (-1);
	if (tcgetattr(0, &term) != 0)
		return (-1);
	term.c_lflag &= ~(ECHO | ECHOE | ICANON);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, 0, &term) != 0)
		return (-1);

	buff = malloc(1000);
	//tputs(tgetstr("ti", &buff), 1, putch);
	ft_printf("test\n");
	tputs(tgetstr("le", &buff), 1, putch);
	tputs(tgetstr("le", &buff), 1, putch);
	tputs(tgetstr("le", &buff), 1, putch);
	ft_printf("V\n");
//	tputs(tgetstr("vi", &buff), 1, putch);

	return (0);
}
