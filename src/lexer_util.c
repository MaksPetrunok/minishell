/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:26:31 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/30 23:19:16 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		append_tkn(t_token **tkn, char **s)
{
	(*tkn)->data[(*tkn)->pos++] = **s;
	(*tkn)->data[(*tkn)->pos] = '\0';
	return (0);
}

int		new_emp_tkn(t_token **tkn, char **s)
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

int		escape(t_token **tkn, char **s)
{
	(*s)++;
	return (append_tkn(tkn, s));
}

int		add_space(t_token **tkn, char __attribute__((unused)) **s)
{
	(*tkn)->complete = 1;
	return (0);
}

int		unexpected_tkn(t_token __attribute__((unused)) **tkn, char **s)
{
	ft_dprintf(2, "%s: syntax error near unexpected token '%c'\n", SHELL_NAME, **s);
	return (-2);
}
