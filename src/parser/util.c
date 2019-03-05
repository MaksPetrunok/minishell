/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 19:19:19 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 17:25:15 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char			*token_to_str(t_token *tkn)
{
	if (tkn->type == T_SEMI)
		return (";");
	else if (tkn->type == T_NEWLINE)
		return ("newline");
	else if (tkn->type == T_PIPE)
		return ("|");
	else if (tkn->type == T_OR)
		return ("||");
	else if (tkn->type == T_AND)
		return ("&&");
	else
		return (tkn->data);
}

t_token			*skip_token(t_token *tkn)
{
	t_token	*tmp;

	if (!tkn)
		return (NULL);
	tmp = tkn;
	tkn = tkn->next;
	if (tkn)
		tkn->prev = NULL;
	free(tmp->data);
	free(tmp);
	return (tkn);
}

int				check_cmd(t_token *tkn)
{
	while (tkn)
	{
		if (tkn->type == T_IO_NUM &&
			(tkn->next == NULL || tkn->next->type != T_WORD))
		{
			ft_printf("syntax error after token '%s'\n", token_to_str(tkn));
			return (0);
		}
		tkn = (tkn->type == T_IO_NUM) ? tkn->next->next : tkn->next;
	}
	return (1);
}

enum e_ntype	type_trans(enum e_tkn_type type)
{
	if (type == T_NEWLINE)
		return (NEWLINE);
	else if (type == T_SEMI)
		return (SEMI);
	else if (type == T_OR)
		return (OR);
	else if (type == T_AND)
		return (AND);
	else if (type == T_PIPE)
		return (PIPE);
	else
		return (COMMAND);
}
