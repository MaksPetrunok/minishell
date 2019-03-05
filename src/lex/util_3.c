/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:26:31 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 18:20:40 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			tkn_ionumb(t_token **tkn, char **s)
{
	t_token	*new;

	if (!(*tkn) || (*tkn)->complete || !ft_isnumeric((*tkn)->data))
	{
		if ((new = init_token(ft_strlen(*s), *tkn)) == NULL)
			return (-1);
		*tkn = new;
	}
	tkn_append(tkn, s);
	if (ft_strnstr(*s, ">>", 2) == *s || ft_strnstr(*s, "<<", 2) == *s ||
		ft_strnstr(*s, ">&", 2) == *s || ft_strnstr(*s, "<&", 2) == *s)
	{
		(*s)++;
		tkn_append(tkn, s);
	}
	(*tkn)->type = T_IO_NUM;
	(*tkn)->complete = 1;
	return (0);
}

int			tkn_complete(t_token **tkn, char **s)
{
	(void)s;
	if (*tkn)
	{
		(*tkn)->complete = 1;
		if ((*tkn)->type == -1)
			(*tkn)->type = T_WORD;
	}
	return (0);
}

int			tkn_logic(t_token **tkn, char **s)
{
	t_token	*new;

	if ((new = init_token(2, *tkn)) == NULL)
		return (-1);
	if (ft_strnstr(*s, "||", 2) == *s)
		new->type = T_OR;
	else if (ft_strnstr(*s, "&&", 2) == *s)
		new->type = T_AND;
	else if (**s == '|')
		new->type = T_PIPE;
	else
		new->type = T_AMP;
	tkn_append(&new, s);
	if (**s == *(*s + 1))
	{
		*s += 1;
		tkn_append(&new, s);
	}
	new->complete = 1;
	*tkn = new;
	return (0);
}

static int	contains_name(char *str)
{
	if (!(*str) || (!ft_isalpha(*str) && *str != '_'))
		return (0);
	else
		str++;
	while (*str)
	{
		if (ft_isalnum(*str) || *str == '_')
			str++;
		else
			return (0);
	}
	return (1);
}

int			tkn_assign(t_token **tkn, char **s)
{
	if (*tkn && !((*tkn)->complete) &&
		(
			(*tkn)->prev == NULL ||
			(*tkn)->prev->type == T_NEWLINE ||
			(*tkn)->prev->type == T_SEMI ||
			(*tkn)->prev->type == T_ASSIGN) &&
		contains_name((*tkn)->data))
	{
		(*tkn)->type = T_ASSIGN;
	}
	tkn_append(tkn, s);
	if ((*tkn)->src == NULL)
		(*tkn)->src = *s;
	return (0);
}
