/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 10:12:24 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/05 17:04:55 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_key_act	key_action(int code)
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
						{0, &inp_insert}};
	int				i;

	i = -1;
	while (++i < KEY_NUM - 1)
		if (table[i].code == code)
			break ;
	return (table[i].on_key_act);
}
/*
static long			get_char(void)
{
	long	c;

	c = 0;
	if (read(0, &c, 4) > 0)
		return (c);
	return (0);
}
*/

static long			get_char(void)
{
	long	c;
	int		i;
	char	*ptr;


	c = 0;
	i = 4;
	ptr = (char *)(&c);
	if (read(0, ptr, 1) < 1)
		return (0);
	if (*ptr >= 0 && *ptr <= 127)
		return (c);
	else if (((*ptr >> 5) & 0b110) == 0b110)
		read(0, ptr + 1, 1);
	else if (((*ptr >> 4) & 0b1110) == 0b1110)
		read(0, ptr + 1, 2);
	else if (((*ptr >> 5) & 0b11110) == 0b11110)
		read(0, ptr + 1, 3);
	return (c);
}

char				*utf_to_str(long *arr, int size)
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
//	techo("Converting...\n");//
	return (str);
}

int					get_input(char **str)
{
	t_inp_buff	*buff;
	t_key_act	on_key;
	int			c;
	int			len;

	if ((buff = init_input_buff()) == 0)
		return (0);
	if (init_keyboard() == 0)
	{
		while (1)
		{
			if ((c = get_char()) == K_RETURN)
			{
				*str = utf_to_str(buff->data, buff->len);
				len = buff->len;
				input_buff_free(buff);
				unset_keyboard();
				return (len);
			}
			on_key = key_action(c);
			on_key(&buff, c);
		}
		unset_keyboard();
	}
	else
		ft_dprintf(2, "%s: cannot set keyboard handler\n", SHELL_NAME);
	return (0);
}
