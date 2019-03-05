/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 09:18:16 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 17:02:32 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_state_trans	g_fsm_table[4][12] =
{
	[S_GEN][CH_GEN] = {S_GEN, &tkn_add},
	[S_GEN][CH_ESC] = {S_GEN, &tkn_escgen},
	[S_GEN][CH_SQT] = {S_SQT, NULL},
	[S_GEN][CH_DQT] = {S_DQT, NULL},
	[S_GEN][CH_EXP] = {S_GEN, &expand_str},

	[S_SQT][CH_GEN] = {S_SQT, &tkn_add},
	[S_SQT][CH_ESC] = {S_SQT, &tkn_add},
	[S_SQT][CH_SQT] = {S_GEN, NULL},
	[S_SQT][CH_DQT] = {S_SQT, &tkn_add},
	[S_SQT][CH_EXP] = {S_SQT, &tkn_add},

	[S_DQT][CH_GEN] = {S_DQT, &tkn_add},
	[S_DQT][CH_ESC] = {S_DQT, &tkn_escdqt},
	[S_DQT][CH_SQT] = {S_DQT, &tkn_add},
	[S_DQT][CH_DQT] = {S_GEN, NULL},
	[S_DQT][CH_EXP] = {S_DQT, &tkn_add}
};

static enum e_signal	get_signal(char c)
{
	if (c == '\\')
		return (CH_ESC);
	else if (c == '\'')
		return (CH_SQT);
	else if (c == '\"')
		return (CH_DQT);
	else if (c == '$' || c == '~') // || c == '`')
		return (CH_EXP);
	else 
		return (CH_GEN);
}

/*
** Initiates new empty token with 'size' bytes allocated for data.
*/

static int		iterate(char *input, t_token *token, enum e_state *st)
{
	enum e_signal	sig;
	t_lex_func		do_action;

	while (*input)
	{
		sig = get_signal(*input);
		if ((do_action = g_fsm_table[*st][sig].func) != 0)
			if (do_action(&token, &input) < 0)
			{
				ft_dprintf(2, "%s: error while parsing input\n", SHELL_NAME);
				return (-1);
			}
		*st = g_fsm_table[*st][sig].state;
		if (*input)
			input++;
	}
	return (0);
}

static void	expand_token(t_token *tkn)
{
	enum e_state	st;
	char			*tmp;

	tmp = tkn->data;
	tkn->size = ft_strlen(tmp);
	tkn->complete = 0;
	if ((tkn->data = malloc(tkn->size + 1)) == NULL)
	{
		tkn->data = tmp;
		ft_dprintf(2, "allocation error during expansion token '%s'\n", tmp);
		return ;
	}
	*(tkn->data) = '\0';
	tkn->pos = 0;
	st = S_GEN;
	if (iterate(tmp, tkn, &st) == -1)
		ft_dprintf(2, "error during parameters expansion in: %s\n", tmp);
	free((void *)tmp);
}

void	expand_tokens(t_token *lst)
{
	while (lst)
	{
		expand_token(lst);
		lst = lst->next;
	}
}
