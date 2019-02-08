/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:26:31 by mpetruno          #+#    #+#             */
/*   Updated: 2019/01/30 19:00:47 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_tkn_type(enum e_tkn_type type)
{
	switch (type)
	{
		case T_WORD: 	return "WORD"; break;
		case T_IO_NUM: 	return "I/O"; break;
		case T_ASSIGN: 	return "ASSI"; break;
		case T_AND: 	return "&&"; break;
		case T_OR:		return "||"; break;
		case T_AMP:		return "&"; break;
		case T_PIPE:	return "|"; break;
		case T_NEWLINE: return "N/L"; break;
		default:		return "!N/A";
	}
}

/*
 * Mark current token as complete, make T_NEWLINE token and mark as complete.
 */
int		tkn_newline(t_token **tkn, char **s)
{
	t_token	*new;

	(void)s;
	if ((new = init_token(0, *tkn)) == NULL)
		return (-1);
	new->type = T_NEWLINE;
	new->complete = 1;
	*tkn = new;
	return (0);
}

/*
 * Mark current token as complete, make new token and add symbol to it.
 */
int		tkn_create(t_token **tkn, char **s)
{
	t_token			*new;

	if ((new = init_token(ft_strlen(*s), *tkn)) == NULL)
		return (-1);
	tkn_append(tkn, s);	
	return (0);
}

/*
 * Append character to current token.
 */
int		tkn_append(t_token **tkn, char **s)
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
	return (0);
}

/*
 * Process escape sequense according to POSIX for esc. sequense out of quotes.
 */
int		tkn_escape(t_token **tkn, char **s)
{
	if (*(*s + 1) == '\n')
		*s += 1;
	else
	{
		tkn_append(tkn, s);
		if (**s != '\0')
		{
			(*s)++;
			tkn_append(tkn, s);
		}
	}
	return (0);
}

int		open_braces(t_token **tkn, char **s, char br)
{
	int	count;

	count = 1;
	while (**s)
	{
		if (**s == br)
			count++;
		else if (**s == '}')
			count--;
		tkn_append(tkn, s);
		if (count == 0)
			break ;
	}
	return (count);
}

/*
 * Find all characters related to expansion and add to current token.
 */
int		tkn_expans(t_token **tkn, char **s)
{
	tkn_append(tkn, s);
	if (**s == '{')
	{
		tkn_append(tkn, s);
		if (open_braces(tkn, s, '{') != 0)
		{
			ft_dprintf(2, "no matching '}' brace found\n");
			return (-1);
		}
	}
	else
		while (**s && ft_isalnum(**s))
			tkn_append(tkn, s);
	return (0);
}



static void	append_fd(t_token **tkn, char **s)
{
	if (*(*s + 1) == '-')
	{
		(*s)++;
		tkn_append(tkn, s);
	}
	else
	{
		while (ft_isdigit(*(*s + 1)))
		{
			(*s)++;
			tkn_append(tkn, s);
		}
	}
}
/*
 * Find all characters related to I/O redirection token and add to current token.
 * If all data contained at this point in the token represents a number - append 
 * new characters to current token, otherwise delimit current token and create new
 * token with default file descriptor for current redirection.
 * After characters added, mark token as complete.
 */
int		tkn_ionumb(t_token **tkn, char **s)
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

	if (**s == '&')
		append_fd(tkn, s);
	(*tkn)->type = T_IO_NUM;
	(*tkn)->complete = 1;
	return (0);
}

/*
 * Mark current token as complete.
 */
int		tkn_complete(t_token **tkn, char **s)
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

/*
 * Find all characters related to &&, ||, & or |, create corresponding token
 * and mark it as complete.
 */
int		tkn_logic(t_token **tkn, char **s)
{
	t_token	*new;

	if ((new = init_token(0, *tkn)) == NULL)
		return (-1);
	if (ft_strnstr(*s, "||", 2) == *s)
		new->type = T_OR;
	else if (ft_strnstr(*s, "&&", 2) == *s)
		new->type = T_AND;
	else if (**s == '|')
		new->type = T_PIPE;
	else
		new->type = T_AMP;
	if (**s == *(*s + 1))
		*s += 1;
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

int		tkn_assign(t_token **tkn, char **s)
{
	if (*tkn && !((*tkn)->complete) &&
		(
			(*tkn)->prev == NULL ||
			(*tkn)->prev->type == T_NEWLINE ||
			(*tkn)->prev->type == T_ASSIGN
		) &&
		contains_name((*tkn)->data)
	)
	{
		(*tkn)->type = T_ASSIGN;
	}
	tkn_append(tkn, s);
	return (0);
}
