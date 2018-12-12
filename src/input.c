/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 10:12:24 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/12 19:27:26 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	key_action(t_inp_buff **buff, int code)
{
	static t_key	table[KEY_NUM] = {
						{K_LEFT, &inp_move},
						{K_RIGHT, &inp_move},
						{K_BACK_SP, &inp_delete},
						{K_DEL, &inp_delete},
						{K_TAB, &inp_autocomp},
						{K_CTRL_D, &inp_exit},
						{K_UP, &inp_ignore},
						{K_DOWN, &inp_ignore},
						{K_CTRL_R, &inp_ignore},
						{K_ALT_LEFT, &inp_ignore},
						{K_ALT_RIGHT, &inp_ignore},
						{0, &inp_ignore},
						{-1, &inp_insert}};
	int				i;

	i = -1;
	while (++i < KEY_NUM - 1)
		if (table[i].code == code)
			break ;
	table[i].on_key_act(buff, code);
}

static long	get_esc(long *c)
{
	char	*ptr;

	ptr = (char *)c;
	if (read(0, ptr + 1, 1) < 1)
		return (0);
	if (*(ptr + 1) == 91)
	{
		read(0, ptr + 2, 5);
		return (*c);
	}
	return (0);
}

static long	get_char(void)
{
	long	c;
	char	*ptr;

	c = 0;
	ptr = (char *)(&c);
	if (read(0, ptr, 1) < 1)
		return (0);
	if (*ptr == 27)
		return (get_esc(&c));
	else if (*ptr >= 0 && *ptr != 27)
		return (c);
	else if (((*ptr >> 5) & 0b110) == 0b110)
		read(0, ptr + 1, 1);
	else if (((*ptr >> 4) & 0b1110) == 0b1110)
		read(0, ptr + 1, 2);
	else if (((*ptr >> 3) & 0b11110) == 0b11110)
		read(0, ptr + 1, 3);
	else
		return (0);
	return (c);
}

char		*utf_to_str(long *arr, int size)
{
	char	*str;
	char	*ptr;
	char	*tmp;

	if ((str = malloc(size + 1)) == 0)
		return (0);
	ptr = str;
	while (*arr)
	{
		tmp = (char *)arr;
		while (*tmp)
			*ptr++ = *tmp++;
		arr++;
	}
	*ptr = '\0';
	return (str);
}

int			get_input(char **str)
{
	t_inp_buff	**buff;
	int			c;
	int			len;

	if (g_shell.canonical)
		return (get_next_line(0, str));
	g_shell.input = init_input_buff();
	buff = &(g_shell.input);
	if (*buff == NULL)
		return (0);
	while (1)
	{
		if ((c = get_char()) == K_RETURN)
		{
			*str = utf_to_str((*buff)->data, (*buff)->len);
			len = (*buff)->len;
			input_buff_free(*buff);
			g_shell.input = NULL;
			return (len);
		}
		key_action(buff, c);
	}
	return (0);
}
