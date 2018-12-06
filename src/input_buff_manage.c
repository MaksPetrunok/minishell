/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_buff_manage.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 16:30:46 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/06 16:55:47 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	inp_insert(t_inp_buff **buff, int key_code)
{
	if ((*buff)->len == (*buff)->size - 1)
	{
		if (!increase_input_buff(buff))
			return (0);
	}
	shift(*buff, 1);
	(*buff)->data[(*buff)->pos] = key_code;
	(*buff)->pos += 1;
	(*buff)->len += 1;
	term_print(key_code);
	return (1);
}

int	inp_move(t_inp_buff **buff, int key_code)
{
	if (key_code == K_LEFT && (*buff)->pos > 0)
	{
		(*buff)->pos--;
		term_cursor_move(key_code);
		return (1);
	}
	else if (key_code == K_RIGHT && (*buff)->pos < (*buff)->len)
	{
		(*buff)->pos++;
		term_cursor_move(key_code);
		return (1);
	}
	return (0);
}

int	inp_delete(t_inp_buff **buff, int key_code)
{
	if (key_code == K_DEL)
	{
		shift(*buff, -1);
		term_delete(key_code);
		(*buff)->len--;
		return (1);
	}
	else if (key_code == K_BACK_SP && (*buff)->pos > 0)
	{
		(*buff)->pos--;
		shift(*buff, -1);
		(*buff)->len--;
		term_delete(key_code);
		return (1);
	}
	return (0);
}

int	inp_ignore(t_inp_buff **buff, int key_code)
{
	(void)buff;
	(void)key_code;
	return (1);
}

int	inp_exit(t_inp_buff **buff, int key_code)
{
	(void)key_code;
	if ((*buff)->len == 0)
	{
		techo("see you later :)\n");
		unset_keyboard();
		exit(0);
	}
	else if ((*buff)->pos < (*buff)->len)
		inp_delete(buff, K_DEL);
	return (1);
}
