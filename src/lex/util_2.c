/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:26:31 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 18:16:42 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		tkn_escgen(t_token **tkn, char **s)
{
	if (*(*s + 1) != '\0')
	{
		*s += 1;
		tkn_append(tkn, s);
	}
	return (0);
}

int		tkn_escdqt(t_token **tkn, char **s)
{
	char	next;

	next = *(*s + 1);
	if (next == '$' || next == '`' || next == '\"' || next == '\\')
	{
		*s += 1;
	}
	tkn_append(tkn, s);
	return (0);
}

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
		else if (**s == ')')
			count--;
		tkn_append(tkn, s);
		(*s)++;
		if (count == 0)
			break ;
	}
	if (**s == '\0' || count == 0)
		(*s)--;
	return (count);
}

int		tkn_expans(t_token **tkn, char **s)
{
	int	braces_rem;

	tkn_append(tkn, s);
	if (*(*s + 1) == '(')
	{
		(*s)++;
		tkn_append(tkn, s);
		(*s)++;
		braces_rem = open_braces(tkn, s, '(');
		if (braces_rem != 0)
		{
			ft_dprintf(2, "no matching ')' brace found\n");
			return (-1);
		}
	}
	return (0);
}
