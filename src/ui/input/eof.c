/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:17:38 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/18 11:10:48 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	inp_eof(t_inp_buff *buff, char *sym)
{
	(void)sym;
	if (g_shell.const_input == NULL && buff->data[0] == NULL)
	{
		write(1, "\n", 1);
		exit_shell();
		exit(0);
	}
	else if (g_shell.const_input == NULL)
	{
		if (buff->pos < buff->len)
			// return ( delete charaacter)
		return (inp_tab(buff, sym));
	}
	if (buff->data[0] == NULL)
		// append Ctrl+D character and handle later in lexer
		;
	return (1);
}
