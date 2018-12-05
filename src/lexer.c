/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:26:31 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/05 15:12:32 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state_trans	g_fsm_table[7][8] =
{
	[S_GENERAL][CH_GENERAL] = {S_GENERAL, &append_tkn},
	[S_GENERAL][CH_VARNAME] = {S_GENERAL, &append_tkn},
	[S_GENERAL][CH_EXPR] = {S_EXPR, &new_emp_tkn},
	[S_GENERAL][CH_ESCAPE] = {S_GENERAL, &escape},
	[S_GENERAL][CH_QUOTE] = {S_QUOTE, 0},
	[S_GENERAL][CH_DQUOTE] = {S_DQUOTE, 0},
	[S_GENERAL][CH_SPACE] = {S_SPACE, &add_space},
	[S_GENERAL][CH_SEMICOLON] = {S_SPECIAL, &new_emp_tkn},

	[S_EXPR][CH_GENERAL] = {S_GENERAL, &new_emp_tkn},
	[S_EXPR][CH_VARNAME] = {S_EXPR, &append_tkn},
	[S_EXPR][CH_EXPR] = {S_EXPR, &append_tkn},
	[S_EXPR][CH_ESCAPE] = {S_ESCAPE, 0},
	[S_EXPR][CH_QUOTE] = {S_QUOTE, &new_emp_tkn},
	[S_EXPR][CH_DQUOTE] = {S_DQUOTE, &new_emp_tkn},
	[S_EXPR][CH_SPACE] = {S_SPACE, &add_space},
	[S_EXPR][CH_SEMICOLON] = {S_SPECIAL, &new_emp_tkn},

	[S_ESCAPE][CH_GENERAL] = {S_GENERAL, &append_tkn},
	[S_ESCAPE][CH_VARNAME] = {S_GENERAL, &append_tkn},
	[S_ESCAPE][CH_EXPR] = {S_GENERAL, &append_tkn},
	[S_ESCAPE][CH_ESCAPE] = {S_GENERAL, &append_tkn},
	[S_ESCAPE][CH_QUOTE] = {S_GENERAL, &append_tkn},
	[S_ESCAPE][CH_DQUOTE] = {S_GENERAL, &append_tkn},
	[S_ESCAPE][CH_SPACE] = {S_GENERAL, &append_tkn},
	[S_ESCAPE][CH_SEMICOLON] = {S_GENERAL, &append_tkn},

	[S_QUOTE][CH_GENERAL] = {S_QUOTE, &append_tkn},
	[S_QUOTE][CH_VARNAME] = {S_QUOTE, &append_tkn},
	[S_QUOTE][CH_EXPR] = {S_QUOTE, &append_tkn},
	[S_QUOTE][CH_ESCAPE] = {S_QUOTE, &append_tkn},
	[S_QUOTE][CH_QUOTE] = {S_GENERAL, 0},
	[S_QUOTE][CH_DQUOTE] = {S_QUOTE, &append_tkn},
	[S_QUOTE][CH_SPACE] = {S_QUOTE, &append_tkn},
	[S_QUOTE][CH_SEMICOLON] = {S_QUOTE, &append_tkn},

	[S_DQUOTE][CH_GENERAL] = {S_DQUOTE, &append_tkn},
	[S_DQUOTE][CH_VARNAME] = {S_DQUOTE, &append_tkn},
	[S_DQUOTE][CH_EXPR] = {S_DQUOTE, &append_tkn},
	[S_DQUOTE][CH_ESCAPE] = {S_DQUOTE, &escape},
	[S_DQUOTE][CH_QUOTE] = {S_DQUOTE, &append_tkn},
	[S_DQUOTE][CH_DQUOTE] = {S_GENERAL, 0},
	[S_DQUOTE][CH_SPACE] = {S_DQUOTE, &append_tkn},
	[S_DQUOTE][CH_SEMICOLON] = {S_DQUOTE, &append_tkn},

	[S_SPACE][CH_GENERAL] = {S_GENERAL, &new_emp_tkn},
	[S_SPACE][CH_VARNAME] = {S_GENERAL, &new_emp_tkn},
	[S_SPACE][CH_EXPR] = {S_EXPR, &new_emp_tkn},
	[S_SPACE][CH_ESCAPE] = {S_ESCAPE, &new_emp_tkn},
	[S_SPACE][CH_QUOTE] = {S_QUOTE, &new_emp_tkn},
	[S_SPACE][CH_DQUOTE] = {S_DQUOTE, &new_emp_tkn},
	[S_SPACE][CH_SPACE] = {S_SPACE, 0},
	[S_SPACE][CH_SEMICOLON] = {S_SPECIAL, &new_emp_tkn},

	[S_SPECIAL][CH_GENERAL] = {S_GENERAL, &new_emp_tkn},
	[S_SPECIAL][CH_VARNAME] = {S_GENERAL, &new_emp_tkn},
	[S_SPECIAL][CH_EXPR] = {S_EXPR, &new_emp_tkn},
	[S_SPECIAL][CH_ESCAPE] = {S_ESCAPE, &new_emp_tkn},
	[S_SPECIAL][CH_QUOTE] = {S_QUOTE, &new_emp_tkn},
	[S_SPECIAL][CH_DQUOTE] = {S_DQUOTE, &new_emp_tkn},
	[S_SPECIAL][CH_SPACE] = {S_SPECIAL, 0},
	[S_SPECIAL][CH_SEMICOLON] = {S_SPECIAL, &unexpected_tkn}
};

enum e_signal	get_signal(char c)
{
	if (c == '\\')
		return (CH_ESCAPE);
	else if (c == '\'')
		return (CH_QUOTE);
	else if (c == '\"')
		return (CH_DQUOTE);
	else if (c == '$' || c == '~')
		return (CH_EXPR);
	else if (c == ' ' || c == '\t')
		return (CH_SPACE);
	else if (c == ';')
		return (CH_SEMICOLON);
	else if (c == '_' || ft_isalnum(c))
		return (CH_VARNAME);
	else if (c != '\0')
		return (CH_GENERAL);
	else
		return (CH_NULL);
}

t_token			*init_token(int size)
{
	t_token	*tkn;
	char	*str;

	tkn = malloc(sizeof(t_token));
	str = malloc(size + 1);
	if (!tkn || !str)
	{
		report_error(ERR_MALLOC);
		return (0);
	}
	*str = '\0';
	tkn->data = str;
	tkn->pos = 0;
	tkn->complete = 0;
	tkn->type = -1;
	tkn->next = 0;
	return (tkn);
}

static int		iterate(char *input, t_token **lst, enum e_state *st)
{
	t_token			*head;
	t_token			*token;
	enum e_signal	sig;
	t_lex_func		do_action;

	head = 0;
	token = *lst;
	while (*input)
	{
		sig = get_signal(*input);
		if ((do_action = g_fsm_table[*st][sig].func) != 0)
			if (do_action(&token, &input) < 0)
			{
				tknlst_free(head);
				ft_dprintf(2, "%s: error while making token list\n",
														SHELL_NAME);
				return (-1);
			}
		head = (!head && token) ? token : head;
		*st = g_fsm_table[*st][sig].state;
		input++;
	}
	*lst = head;
	return (0);
}

t_token			*tokenize(char *input)
{
	t_token			*token;
	enum e_state	st;

	if (!input)
		return (0);
	token = 0;
	st = S_SPECIAL;
	if (iterate(input, &token, &st) == -1)
		return (0);
	if (st == S_QUOTE || st == S_DQUOTE)
	{
		ft_dprintf(2, "%s: unmatched quotes found\n", SHELL_NAME);
		tknlst_free(token);
		return (0);
	}
	return (token);
}
