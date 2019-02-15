/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 09:18:16 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/15 10:16:13 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * 1. Set tkn size to data length.
 * 2. Maloc data as lengh + 1 bytes and set to ""
 * 3. Use FSM to open quotes and perform expansions.
 *
 * Read characters while not $ or ~.
 * - if ~ found:
 *   - replace ~ with \0 in original string
 *   - tmp = ft_strjoin3(str, expand_tilda(), str + 2), check if segfaults possible
 *   - free original string and set tmp instead
 * - if $ found - 
 * Tokens:
 * NEWLINE
 * IO_NUMBER (I/O redirection: pipe, >, <, >> or <<)
 * WORD
 * ASSIGN (variable assignment - only if it is first token, or there is preceeding NEWLINE
 * AND
 * OR
 */

/*
 * States: S_GEN - general (inside word)
 *         S_WSP - whitespace (between words) // not needed? close token upon witespace and go further
 *         S_IOR - I/O redirection (after > or <)
 *         S_SQT - single quote
 *         S_DQT - double quote
 *         S_ESC - escape sequense
 *         S_LOG - logical operator? (after | or &) check if it's pipe, &, && or ||
 */

// Add hash # recognition for comments handling

static t_state_trans	g_fsm_table[4][12] =
{
	[S_GEN][CH_GEN] = {S_GEN, &tkn_append},
	[S_GEN][CH_ESC] = {S_GEN, &tkn_escgen},
	[S_GEN][CH_SQT] = {S_SQT, NULL},
	[S_GEN][CH_DQT] = {S_DQT, NULL},
	[S_GEN][CH_EXP] = {S_GEN, &tkn_expans},

	[S_SQT][CH_GEN] = {S_SQT, &tkn_append},
	[S_SQT][CH_ESC] = {S_SQT, &tkn_append},
	[S_SQT][CH_SQT] = {S_GEN, NULL},
	[S_SQT][CH_DQT] = {S_SQT, &tkn_append},
	[S_SQT][CH_EXP] = {S_SQT, &tkn_append},

	[S_DQT][CH_GEN] = {S_DQT, &tkn_append},
	[S_DQT][CH_ESC] = {S_DQT, &tkn_escdqt},
	[S_DQT][CH_SQT] = {S_DQT, &tkn_append},
	[S_DQT][CH_DQT] = {S_GEN, NULL},
	[S_DQT][CH_EXP] = {S_DQT, &tkn_expans}
};

static enum e_signal	get_signal(char c)
{
	if (c == '\\')
		return (CH_ESC);
	else if (c == '\'')
		return (CH_SQT);
	else if (c == '\"')
		return (CH_DQT);
	else if (c == '$' || c == '~' || c == '`')
		return (CH_EXP);
	else 
		return (CH_GEN);
}

/*
** Initiates new empty token with 'size' bytes allocated for data.
*/

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
				ft_dprintf(2, "%s: error while parsing input\n",
														SHELL_NAME);
				return (-1);
			}
		head = (!head && token) ? token : head;
		*st = g_fsm_table[*st][sig].state;
		input++;
	}
	*lst = head;
	if (token && token->type == -1)
		token->type = T_WORD;
	return (0);
}

static char *get_type(enum e_tkn_type type)
{
	switch (type)
	{
		case T_WORD: 	return "WORD"; break;
		case T_IO_NUM: 	return " I/O"; break;
		case T_ASSIGN: 	return "ASSI"; break;
		case T_AND: 	return " AND"; break;
		case T_OR:		return "  OR"; break;
		case T_AMP:		return " AMP"; break;
		case T_PIPE:	return "PIPE"; break;
		case T_NEWLINE: return " N/L"; break;
		case T_SEMI:	return "SEMI"; break;
		default:		return "!N/A";
	}
}

static void	debug_tknlist(t_token *lst)
{
	while (lst)
	{
		ft_printf("%s: %s\n", get_type(lst->type), lst->data);
		lst = lst->next;
	}
}


t_token			*tokenize(char *input)
{
	t_token			*token;
	enum e_state	st;

	if (!input)
		return (0);
ft_printf("DEBUG: start tokenizing ----------------------------\n");
	token = 0;
	st = S_GEN;
	if (iterate(input, &token, &st) == -1)
	{
		ft_printf("debug: NULL returned.\n"); // for debug
		exit(0);                              // for debug
		return (0);
	}
	if (st == S_SQT || st == S_DQT)
	{
		ft_dprintf(2, "%s: parsing error - unmatched quotes found\n", SHELL_NAME);
		tknlst_free(token);
		return (0);
	}
	debug_tknlist(token); // for debug
	//exit(0);              // for debug
	ft_printf("========== END LEXER ===============\n");
	return (token);
}
