/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 11:52:22 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/06 22:40:04 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	myputchar(int c)
{
	return (write(0, &c, 4));
}

int	techo(char *s)
{
//	unset_keyboard();
	ft_putstr(s);
	tputs(s, 1, myputchar);
//	init_keyboard();
	return (0);
}

int	tconf(char *s)
{
	char	**buff;

	buff = 0;
	tputs(tgetstr(s, buff), 1, myputchar);
	return (0);
}
