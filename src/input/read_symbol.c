/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_symbol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:18:25 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/26 16:00:43 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_symbol(char *buff, int fd)
{
	int	i;

	read(fd, buff, 1);
	if (*buff == 27)
	{
		i = 2;
		read(fd, buff + 1, 1);
		while (i < SYM_SIZE && is_control(buff) == 1)
		{
			read(fd, buff + i++, 1);
		}
		if (!is_control(buff))
			*buff = '\0';
	}
	else if (*buff > 31)
		return ;
	else if ((*buff >> 5) == 0b110)
		read(fd, buff + 1, 1);
	else if ((*buff >> 4) == 0b1110)
		read(fd, buff + 1, 2);
	else if ((*buff >> 3) == 0b11110)
		read(fd, buff + 1, 3);
}
