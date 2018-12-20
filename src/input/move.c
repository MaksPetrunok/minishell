/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:17:38 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/20 17:13:49 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	putch(int c)
{
	return (write(1, &c, 1));
}

int	inp_movel(t_inp_buff *buff, char *sym)
{
	(void)sym;
	if (buff->pos == 0)
		return (0);
	buff->pos--;
	cur_mv_left();
	return (1);
}

int	inp_mover(t_inp_buff *buff, char *sym)
{
	(void)sym;
	if (buff->pos == buff->len)
		return (0);
	cur_mv_right(0);
	buff->pos++;
	return (1);
}

int	inp_ignore(t_inp_buff *buff, char *sym)
{
	(void)buff;
	(void)sym;
	return (1);
}
