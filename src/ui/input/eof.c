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
	if (g_shell.const_input == NULL && buff->data[0] == NULL)
	{
		write(1, "\n", 1);
		exit_shell();
		exit(0);
	}
	else if (g_shell.const_input == NULL)
	{
		if (buff->pos < buff->len)
			return (inp_delete(buff, sym));
		return (inp_tab(buff, sym));
	}
	if (g_shell.inp_state != S_GEN && g_shell.input->len == 0)
	{
		free((void *)(g_shell.const_input));
		g_shell.inp_state = S_GEN;
		g_shell.input->data[0] = NULL;
		g_shell.input->pos = 0;
		g_shell.input->len = 0;
		g_shell.const_input = NULL;
		write(2, "\nunexpected EOF token\n", 22);
		return (0);
	}
	return (1);
}
