/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_buff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 11:15:12 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/13 21:15:22 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_inp_buff	*init_input_buff(void)
{
	t_inp_buff	*ret;
	long		*data;

	data = malloc((INPUT_BUFF_SIZE) * sizeof(long));
	ret = malloc(sizeof(t_inp_buff));
	if (!data || !ret)
	{
		free((void *)data);
		free((void *)ret);
		ft_dprintf(2, "%s: failed to allocate buffer for input\n", SHELL_NAME);
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
	long		*new_data;
	int			new_size;

	new_size = (*buff)->size + INPUT_BUFF_SIZE;

	if ((new_data = (long *)ft_realloc((void *)((*buff)->data),
								sizeof(long) * (*buff)->size,
								sizeof(long) * new_size)) == 0)
		return (0);
	(*buff)->data = new_data;
	(*buff)->size = new_size;
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
