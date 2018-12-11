/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_buff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 11:15:12 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/10 05:19:50 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_inp_buff	*init_input_buff(void)
{
	t_inp_buff	*ret;
	long		*data;

	data = (long *)malloc((INPUT_BUFF_SIZE) * sizeof(long));
	ret = (t_inp_buff *)malloc(sizeof(t_inp_buff));
	if (!data || !ret)
	{
		techo(SHELL_NAME);
		techo(": failed to allocate buffer for input\n");
		return (0);
	}
	ret->data = data;
	ret->data[0] = 0;
	ret->pos = 0;
	ret->len = 0;
	ret->size = INPUT_BUFF_SIZE;
	return (ret);
}

int			increase_input_buff(t_inp_buff **buff)
{
	t_inp_buff	*new_buff;
	long		*new_data;
	int			new_size;

	new_size = (*buff)->size + INPUT_BUFF_SIZE;
	if ((new_buff = malloc(sizeof(t_inp_buff))) == 0)
		return (0);
	if ((new_data = malloc(sizeof(long) * new_size)) == 0)
	{
		free((void *)new_buff);
		return (0);
	}
	while (--((*buff)->size) >= 0)
		new_data[(*buff)->size] = (*buff)->data[(*buff)->size];
	new_buff->pos = (*buff)->pos;
	new_buff->data = new_data;
	new_buff->size = new_size;
	new_buff->len = (*buff)->len;
	input_buff_free(*buff);
	*buff = new_buff;
	return (1);
}

void		input_buff_free(t_inp_buff *buff)
{
	if (buff == NULL)
		return ;
	free((void *)(buff->data));
	free((void *)buff);
}

void		shift(t_inp_buff *buff, int direction)
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

int			inp_autocomp(t_inp_buff **buff, int key_code)
{
	int	i;

	if ((*buff)->pos == 0)
		return (inp_insert(buff, key_code));
	i = (*buff)->pos;
	while (i > 0)
		if ((*buff)->data[i - 1] != 0 &&
			(*buff)->data[i - 1] != (long)' ' &&
			(*buff)->data[i - 1] != (long)K_TAB)
			return (auto_complete(buff));
		else
			i--;
	//inp_insert(buff, key_code);
	return (inp_insert(buff, key_code));
}
