/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 20:15:58 by mpetruno          #+#    #+#             */
/*   Updated: 2019/01/06 20:16:38 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	increase_buff(t_inp_buff *buff)
{
	int		new_size;
	size_t	new_bytes;
	size_t	old_bytes;
	char	**new_data;

	new_size = buff->size + INP_BUFF_SIZE;
	old_bytes = buff->size * sizeof(char **);
	new_bytes = new_size * sizeof(char **);
	new_data = ft_realloc((void *)(buff->data), old_bytes, new_bytes);
	if (new_data == buff->data || new_data == NULL)
		return (0);
	buff->data = new_data;
	buff->size = new_size;
	return (1);
}
