/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:26:31 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 18:20:14 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		connect_tokens(t_token *prev, t_token *new)
{
	if (prev != NULL)
	{
		prev->next = new;
		tkn_complete(&prev, 0);
		new->prev = prev;
	}
	else
		new->prev = NULL;
}

t_token			*init_token(int size, t_token *prev)
{
	t_token *tkn;

	if ((tkn = malloc(sizeof(t_token))) == NULL)
		return (NULL);
	connect_tokens(prev, tkn);
	if (size > 0)
	{
		if ((tkn->data = malloc(size + 1)) == NULL)
		{
			free((void *)tkn);
			report_error(ERR_MALLOC);
			return (NULL);
		}
		*(tkn->data) = '\0';
	}
	else
		tkn->data = NULL;
	tkn->pos = 0;
	tkn->complete = 0;
	tkn->type = -1;
	tkn->next = NULL;
	tkn->src = NULL;
	return (tkn);
}

int				tkn_newline(t_token **tkn, char **s)
{
	t_token	*new;

	(void)s;
	if ((new = init_token(1, *tkn)) == NULL)
		return (-1);
	new->type = (**s == ';') ? T_SEMI : T_NEWLINE;
	tkn_append(&new, s);
	new->complete = 1;
	new->src = *s;
	*tkn = new;
	return (0);
}

int				tkn_create(t_token **tkn, char **s)
{
	t_token			*new;

	if ((new = init_token(ft_strlen(*s), *tkn)) == NULL)
		return (-1);
	tkn_append(tkn, s);
	(*tkn)->src = *s;
	return (0);
}

int				tkn_append(t_token **tkn, char **s)
{
	if (*tkn == NULL)
	{
		if ((*tkn = init_token(ft_strlen(*s), NULL)) == NULL)
			return (-1);
	}
	else if ((*tkn)->complete)
	{
		if ((*tkn = init_token(ft_strlen(*s), *tkn)) == NULL)
			return (-1);
	}
	(*tkn)->data[(*tkn)->pos++] = **s;
	(*tkn)->data[(*tkn)->pos] = '\0';
	if ((*tkn)->src == NULL)
		(*tkn)->src = *s;
	return (0);
}
