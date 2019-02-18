/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 18:59:19 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/18 11:10:16 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	inp_copy_all(t_inp_buff *buff, char *sym)
{
	(void)sym;
	free((void *)(g_shell.clipboard));
	g_shell.clipboard = inp_to_str(buff->data);
	return (0);
}

int	inp_copy_backward(t_inp_buff *buff, char *sym)
{
	char	*tmp;

	(void)sym;
	tmp = buff->data[buff->pos];
	buff->data[buff->pos] = NULL;
	inp_copy_all(buff, 0);
	buff->data[buff->pos] = tmp;
	return (0);
}

int	inp_copy_forward(t_inp_buff *buff, char *sym)
{
	(void)sym;
	free((void *)(g_shell.clipboard));
	g_shell.clipboard = inp_to_str(buff->data + buff->pos);
	return (0);
}
