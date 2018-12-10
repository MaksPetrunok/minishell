/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 19:58:48 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/10 07:31:21 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_cursor(void)
{
	if ((shell.cursor = malloc(sizeof(t_cursor))) == 0)
		return (-1);
	shell.cursor->col = 0;
	shell.cursor->row = 0;
	return (0);
}
