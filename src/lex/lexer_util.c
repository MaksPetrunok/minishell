/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:26:31 by mpetruno          #+#    #+#             */
/*   Updated: 2019/01/28 19:28:07 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Mark current token as complete, make T_NEWLINE token and mark as complete.
 */
int		tkn_newline(t_token **tkn, char **s)
{
	t_token	*new;

	(void)s;
	(*tkn)->complete = 1;
	if ((new = init_token(0)) == NULL)
		return (-1);
	(*tkn)->next = new;
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
	enum e_signal	sig;

	sig = get_signal(**s);
	if (**s && (new = init_token(
		(sig == CH_SEMICOLON) ? 2 : ft_strlen(*s))) == 0)
		return (-1);
	if (sig == CH_EXPR || sig == CH_SEMICOLON)
		new->type = sig;
	else
		new->type = CH_GENERAL;
	if (sig == CH_GENERAL || sig == CH_VARNAME || sig == CH_EXPR)
		append_tkn(&new, s);
	else
		new->data[new->pos] = '\0';
	if (*tkn == 0)
		*tkn = new;
	else
	{
		(*tkn)->next = new;
		*tkn = new;
	}
	return (0);
}

/*
 * Append character to current token.
 */
int		tkn_append(t_token **tkn, char **s)
{
	(*tkn)->data[(*tkn)->pos++] = **s;
	(*tkn)->data[(*tkn)->pos] = '\0';
	return (0);
}

/*
 * Process escape sequense according to POSIX for esc. sequense out of quotes.
 */
int		tkn_escgen(t_token **tkn, char **s)
{
	(*s)++;
	return (append_tkn(tkn, s));
}

/*
 * Process escape sequense according to POSIX for esc. sequense within double quotes.
 */
int		tkn_escdqt(t_token **tkn, char **s)
{
	(*s)++;
	return (append_tkn(tkn, s));
}

/*
 * Find all characters related to expansion and add to current token.
 */
int		tkn_expans(t_token **tkn, char __attribute__((unused)) **s)
{
	(*tkn)->complete = 1;
	return (0);
}

/*
 * Find all characters related to I/O redirection token and add to current token.
 * If all data contained at this point in the token represents a number - append 
 * new characters to current token, otherwise delimit current token and create new
 * token with default file descriptor for current redirection.
 * After characters added, mark token as complete.
 */
int		tkn_ionumb(t_token __attribute__((unused)) **tkn, char **s)
{
	ft_dprintf(2, "%s: syntax error near unexpected token '%c'\n",
													SHELL_NAME, **s);
	return (-2);
}

/*
 * Mark current token as complete.
 */
int		tkn_complete(t_token __attribute__((unused)) **tkn, char **s)
{
	ft_dprintf(2, "%s: syntax error near unexpected token '%c'\n",
													SHELL_NAME, **s);
	return (-2);
}

/*
 * Find all characters related to &&, ||, & or |, create corresponding token
 * and mark it as complete.
 */
int		tkn_logic(t_token __attribute__((unused)) **tkn, char **s)
{
	ft_dprintf(2, "%s: syntax error near unexpected token '%c'\n",
													SHELL_NAME, **s);
	return (-2);
}
