/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_outp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 18:47:24 by mpetruno          #+#    #+#             */
/*   Updated: 2019/01/06 17:43:32 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	putchar_echo(int c)
{
	return (write(0, &c, 1));
}

static int	putchar_conf(int c)
{
	return (write(1, &c, 1));
}

int			techo(char *s)
{
	tputs(s, 1, putchar_echo);
	return (0);
}

int			tconf(char *s)
{
	tputs(tgetstr(s, 0), 1, putchar_conf);
	return (0);
}

void		move_cursor(int col, int row)
{
	tputs(tgoto(tgetstr("cm", 0), col, row), 1, putchar_conf);
}
