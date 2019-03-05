/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:26:31 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 18:11:34 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_state_trans	g_fsm_table[5][13] =
{
	[S_GEN][CH_GEN] = {S_GEN, &tkn_append},
	[S_GEN][CH_NLN] = {S_GEN, &tkn_newline},
	[S_GEN][CH_SCL] = {S_GEN, &tkn_newline},
	[S_GEN][CH_ESC] = {S_GEN, &tkn_escape},
	[S_GEN][CH_SQT] = {S_SQT, &tkn_append},
	[S_GEN][CH_DQT] = {S_DQT, &tkn_append},
	[S_GEN][CH_BQT] = {S_BQT, &tkn_append},
	[S_GEN][CH_EXP] = {S_GEN, &tkn_expans},
	[S_GEN][CH_IOR] = {S_GEN, &tkn_ionumb},
	[S_GEN][CH_LOG] = {S_GEN, &tkn_logic},
	[S_GEN][CH_EQU] = {S_GEN, &tkn_assign},
	[S_GEN][CH_HSH] = {S_HSH, NULL},
	[S_GEN][CH_WSP] = {S_GEN, &tkn_complete},

	[S_SQT][CH_GEN] = {S_SQT, &tkn_append},
	[S_SQT][CH_NLN] = {S_SQT, &tkn_append},
	[S_SQT][CH_ESC] = {S_SQT, &tkn_append},
	[S_SQT][CH_SCL] = {S_SQT, &tkn_append},
	[S_SQT][CH_SQT] = {S_GEN, &tkn_append},
	[S_SQT][CH_DQT] = {S_SQT, &tkn_append},
	[S_SQT][CH_BQT] = {S_SQT, &tkn_append},
	[S_SQT][CH_EXP] = {S_SQT, &tkn_append},
	[S_SQT][CH_IOR] = {S_SQT, &tkn_append},
	[S_SQT][CH_LOG] = {S_SQT, &tkn_append},
	[S_SQT][CH_EQU] = {S_SQT, &tkn_append},
	[S_SQT][CH_HSH] = {S_SQT, &tkn_append},
	[S_SQT][CH_WSP] = {S_SQT, &tkn_append},

	[S_DQT][CH_GEN] = {S_DQT, &tkn_append},
	[S_DQT][CH_NLN] = {S_DQT, &tkn_append},
	[S_DQT][CH_ESC] = {S_DQT, &tkn_escape},
	[S_DQT][CH_SCL] = {S_DQT, &tkn_append},
	[S_DQT][CH_SQT] = {S_DQT, &tkn_append},
	[S_DQT][CH_DQT] = {S_GEN, &tkn_append},
	[S_DQT][CH_BQT] = {S_DQT, &tkn_append},
	[S_DQT][CH_EXP] = {S_DQT, &tkn_expans},
	[S_DQT][CH_IOR] = {S_DQT, &tkn_append},
	[S_DQT][CH_LOG] = {S_DQT, &tkn_append},
	[S_DQT][CH_EQU] = {S_DQT, &tkn_append},
	[S_DQT][CH_HSH] = {S_DQT, &tkn_append},
	[S_DQT][CH_WSP] = {S_DQT, &tkn_append},

	[S_BQT][CH_GEN] = {S_BQT, &tkn_append},
	[S_BQT][CH_NLN] = {S_BQT, &tkn_append},
	[S_BQT][CH_ESC] = {S_BQT, &tkn_append},
	[S_BQT][CH_SCL] = {S_BQT, &tkn_append},
	[S_BQT][CH_SQT] = {S_BQT, &tkn_append},
	[S_BQT][CH_DQT] = {S_BQT, &tkn_append},
	[S_BQT][CH_BQT] = {S_GEN, &tkn_append},
	[S_BQT][CH_EXP] = {S_BQT, &tkn_append},
	[S_BQT][CH_IOR] = {S_BQT, &tkn_append},
	[S_BQT][CH_LOG] = {S_BQT, &tkn_append},
	[S_BQT][CH_EQU] = {S_BQT, &tkn_append},
	[S_BQT][CH_HSH] = {S_BQT, &tkn_append},
	[S_BQT][CH_WSP] = {S_BQT, &tkn_append},

	[S_HSH][CH_GEN] = {S_HSH, NULL},
	[S_HSH][CH_NLN] = {S_GEN, NULL},
	[S_HSH][CH_SCL] = {S_HSH, NULL},
	[S_HSH][CH_ESC] = {S_HSH, NULL},
	[S_HSH][CH_SQT] = {S_HSH, NULL},
	[S_HSH][CH_DQT] = {S_HSH, NULL},
	[S_HSH][CH_BQT] = {S_HSH, NULL},
	[S_HSH][CH_EXP] = {S_HSH, NULL},
	[S_HSH][CH_IOR] = {S_HSH, NULL},
	[S_HSH][CH_LOG] = {S_HSH, NULL},
	[S_HSH][CH_EQU] = {S_HSH, NULL},
	[S_HSH][CH_HSH] = {S_HSH, NULL},
	[S_HSH][CH_WSP] = {S_HSH, NULL}
};

static enum e_signal	get_signal(char c)
{
	if (c == '\\')
		return (CH_ESC);
	else if (c == '\'' || c == '\"')
		return (c == '\'' ? CH_SQT : CH_DQT);
	else if (c == '`')
		return (CH_BQT);
	else if (c == '$')
		return (CH_EXP);
	else if (c == '<' || c == '>')
		return (CH_IOR);
	else if (c == '|' || c == '&')
		return (CH_LOG);
	else if (c == ' ' || c == '\t')
		return (CH_WSP);
	else if (c == '\n')
		return (CH_NLN);
	else if (c == ';')
		return (CH_SCL);
	else if (c == '#')
		return (CH_HSH);
	else if (c == '=')
		return (CH_EQU);
	else
		return (CH_GEN);
}

static int				iterate(char *input, t_token **lst, enum e_state *st)
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
				ft_dprintf(2, "%s: error while parsing input\n", SHELL_NAME);
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

t_token					*tokenize(char *input)
{
	t_token			*token;
	enum e_state	st;

	if (!input)
		return (0);
	token = 0;
	st = S_GEN;
	if (iterate(input, &token, &st) == -1)
	{
		tknlst_free(token);
		return (NULL);
	}
	g_shell.inp_state = st;
	if (st == S_SQT || st == S_DQT || st == S_BQT)
	{
		g_shell.const_input = ft_strdup(input);
		tknlst_free(token);
		return (NULL);
	}
	return (token);
}

void					tknlst_free(t_token *lst)
{
	t_token	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free((void *)(lst->data));
		free((void *)lst);
		lst = tmp;
	}
}
