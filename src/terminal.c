/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 11:52:22 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/05 11:36:57 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	myputchar(int c)
{
	return (write(1, &c, 4));
}

int	techo(char *s)
{
	tputs(s, 1, myputchar);
	return (0);
}

int	tconf(char *s)
{
	char	**buff;

	buff = 0;
	tputs(tgetstr(s, buff), 1, myputchar);
	return (0);
}

int	init_keyboard(void)
{
	struct termios	tmp;

	if (tgetent(0, get_var("TERM")) != 1)
		return (-1);
	if (tcgetattr(0, &g_term) != 0)
		return (-1);
	ft_memcpy((void *)&tmp, (void *)&g_term, sizeof(struct termios));
	tmp.c_lflag &= ~(ECHO | ECHOE | ICANON);
	tmp.c_cc[VMIN] = 1;
	tmp.c_cc[VTIME] = 0;
	if (tcsetattr(0, 0, &tmp) != 0)
		return (-1);
	tconf("im");
	return (0);
}

int	unset_keyboard(void)
{
	tconf("ei");
	if (tcsetattr(0, 0, &g_term) != 0)
		return (-1);
	return (0);
}
