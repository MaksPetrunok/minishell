/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 16:51:50 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/15 16:57:34 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tkn_add(t_token **token, char **inp)
{
	char	*new;
	t_token	*tkn;

	tkn = *token;
	if (tkn->size == tkn->pos)
	{
		if ((new = malloc(tkn->size + 32)) == NULL)
		{
			ft_dprintf(2, "allocation error\n");
			return (-1);
		}
		ft_strcpy(new, tkn->data);
		free((void *)(tkn->data));
		tkn->data = new;
	}
	return (tkn_append(token, inp));
}
