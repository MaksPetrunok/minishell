/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_buff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 11:15:12 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/04 22:41:32 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_inp_buff	*init_input_buff(void)
{
	t_inp_buff	*ret;
	long		*data;

	data = malloc(INPUT_BUFF_SIZE * sizeof(int));
	ret = malloc(sizeof(t_inp_buff));
	if (!data || !ret)
	{
		tputs(SHELL_NAME, 1, myputchar);
		tputs(": failed to allocate buffer for input\n", 1, myputchar);
		return (0);
	}
	ret->data = data;
	ret->data[0] = 0;

	ret->pos = 0;
	ret->len = 0;
	ret->size = INPUT_BUFF_SIZE;
	return (ret);
}

void		input_buff_free(t_inp_buff *buff)
{
	free((void *)(buff->data));
	free((void *)buff);
}

static void	shift(t_inp_buff *buff, int direction)
{
	int	i;

	if (direction > 0)
	{
		i = buff->len;
		while (i >= buff->pos)
		{
			buff->data[i + 1] = buff->data[i];
			i--;
		}
	}
	else if (direction < 0)
	{
		i = buff->pos;
		while (i < buff->len)
		{
			buff->data[i] = buff->data[i + 1];
			i++;
		}
	}
}

int			increase_input_buff(t_inp_buff **buff)
{
	long	*new_data;
	int		new_size;

	new_size = (*buff)->size + INPUT_BUFF_SIZE;
	if ((new_data = malloc(sizeof(long) * new_size)) == 0)
		return (0);
	ft_memcpy((void *)new_data, (void *)(*buff)->data,
							(*buff)->size * sizeof(long));
	free((void *)(*buff)->data);
	(*buff)->data = new_data;
	(*buff)->size = new_size;
	return (1);
}

int			inp_insert(t_inp_buff *buff, int key_code)
{
	if (buff->len == buff->size - 1)
		if (!increase_input_buff(&buff))
			return (0);
	shift(buff, 1);
	buff->data[buff->pos] = key_code;
	buff->pos += 1;
	buff->len += 1;
	term_print(key_code);
	return (1);
}

int			inp_move(t_inp_buff *buff, int key_code)
{
	if (key_code == K_LEFT && buff->pos > 0)
	{
		buff->pos--;
		term_cursor_move(key_code);
		return (1);
	}
	else if (key_code == K_RIGHT && buff->pos < buff->len)
	{
		buff->pos++;
		term_cursor_move(key_code);
		return (1);
	}
	return (0);

}

int			inp_delete(t_inp_buff *buff, int key_code)
{
	if (key_code == K_DEL)
	{
		shift(buff, -1);
		term_delete(key_code);
		buff->len--;
		return (1);
	}
	else if (key_code == K_BACK_SP && buff->pos > 0)
	{
		buff->pos--;
		shift(buff, -1);
		buff->len--;
		term_delete(key_code);
		return (1);
	}
	return (0);

}

int			inp_ignore(t_inp_buff UNUSED *buff, int UNUSED key_code)
{
	return (1);
}

int			inp_exit(t_inp_buff *buff, int UNUSED key_code)
{
	if (buff->len == 0)
	{
		tputs("see you later :)\n", 1, myputchar);
		unset_keyboard();
		exit(0);
	}
	else if (buff->pos < buff->len)
		inp_delete(buff, K_DEL);
	return (1);

}

int			inp_autocomp(t_inp_buff UNUSED *buff, int UNUSED key_code)
{
	auto_complete(buff);
//	tputs("AUTOCOMPLETION\n", 1, myputchar);
	return (1);
}
