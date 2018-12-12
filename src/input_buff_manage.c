/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_buff_manage.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 16:30:46 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/12 22:29:33 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void refresh_str(t_inp_buff *buff)
{
	int		i;
	long	*av;

	i = buff->pos;
	tconf("ce"); // clean not only current line, but all following as well
	av = buff->data;
	while (av[i])
		term_print(av[i++]);
	while (i-- > buff->pos)
		term_cursor_move(K_LEFT);
}

int	inp_insert(t_inp_buff **buff, int key_code)
{
	int	move;

	move = 1;
	if ((*buff)->len == (*buff)->size - 1)
	{
		if (!increase_input_buff(buff))
			return (0);
	}
	shift(*buff, 1);
	(*buff)->data[(*buff)->pos] = key_code;
	(*buff)->pos += 1;
	(*buff)->len += 1;
	if (key_code == K_TAB)
	{
		move = TAB_SIZE;
		key_code = ' ';
	}
	while (move-- > 0)
		term_print(key_code);
	if ((*buff)->pos < (*buff)->len)
		refresh_str(*buff);
	return (1);
}

int	inp_move(t_inp_buff **buff, int key_code)
{
	int	move;

	move = 0;
	if (key_code == K_LEFT && (*buff)->pos > 0)
	{
		(*buff)->pos--;
		if ((*buff)->data[(*buff)->pos] == K_TAB)
			move = TAB_SIZE;
		else
			move = 1;
	}
	else if (key_code == K_RIGHT && (*buff)->pos < (*buff)->len)
	{
		if ((*buff)->data[(*buff)->pos] == K_TAB)
			move = TAB_SIZE;
		else
			move = 1;
		(*buff)->pos++;
	}
	while (move-- > 0)
		term_cursor_move(key_code);
	return (1);
}

int	inp_delete(t_inp_buff **buff, int key_code)
{
	int	move;
	int	can_delete;

	can_delete = (key_code == K_BACK_SP && (*buff)->pos > 0) ||
		key_code == K_DEL;
	if (key_code == K_BACK_SP && (*buff)->pos > 0)
		(*buff)->pos--;
	move = (*buff)->data[(*buff)->pos] == K_TAB ? 4 : 1;
	while (can_delete && move-- > 0)
		term_delete(key_code);
	shift(*buff, -1);
	(*buff)->len--;
	return (1);
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
		techo("exit\n");
		input_buff_free(*buff);
		exit_shell();
		exit(0);
	}
	else if ((*buff)->pos < (*buff)->len)
		inp_delete(buff, K_DEL);
	return (1);
}
