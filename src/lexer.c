/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:26:31 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/30 23:19:16 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_state_trans	g_fsm_table[7][8] =
{
	[S_GENERAL][CH_GENERAL] = {S_GENERAL, &append_tkn},
	[S_GENERAL][CH_VARNAME] = {S_GENERAL, &append_tkn},
	[S_GENERAL][CH_EXPR] = {S_EXPR, &new_exp_tkn},
	[S_GENERAL][CH_ESCAPE] = {S_GENERAL, &escape},
	[S_GENERAL][CH_QUOTE] = {S_QUOTE, 0},
	[S_GENERAL][CH_DQUOTE] = {S_DQUOTE, 0},
	[S_GENERAL][CH_SPACE] = {S_SPACE, &add_space},
	[S_GENERAL][CH_SEMICOLON] = {S_SPECIAL, &new_emp_tkn},

	[S_EXPR][CH_GENERAL] = {S_GENERAL, &new_emp_tkn},
	[S_EXPR][CH_VARNAME] = {S_EXPR, &append_tkn},
	[S_EXPR][CH_EXPR] = {S_EXPR, &append_tkn},
	[S_EXPR][CH_ESCAPE] = {S_ESCAPE, 0}, // make S_ESCAPE unused
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
	[S_SPACE][CH_EXPR] = {S_EXPR, &new_exp_tkn},
	[S_SPACE][CH_ESCAPE] = {S_ESCAPE, &new_emp_tkn},
	[S_SPACE][CH_QUOTE] = {S_QUOTE, &new_emp_tkn},
	[S_SPACE][CH_DQUOTE] = {S_DQUOTE, &new_emp_tkn},
	[S_SPACE][CH_SPACE] = {S_SPACE, 0},
	[S_SPACE][CH_SEMICOLON] = {S_SPECIAL, &new_emp_tkn},

	[S_SPECIAL][CH_GENERAL] = {S_GENERAL, &new_emp_tkn},
	[S_SPECIAL][CH_VARNAME] = {S_GENERAL, &new_emp_tkn},
	[S_SPECIAL][CH_EXPR] = {S_EXPR, &new_exp_tkn},
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
//		report_error(ERR_MALLOC); //uncomment for using with minishell
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

int		append_tkn(t_token **tkn, char **s)
{
	(*tkn)->data[(*tkn)->pos++] = **s;
	(*tkn)->data[(*tkn)->pos] = '\0';
	return (0);
}

int		new_exp_tkn(t_token **tkn, char **s)
{
	return (new_emp_tkn(tkn, s));
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

#define SHELL_NAME "SHELL"

int		unexpected_tkn(t_token __attribute__((unused)) **tkn, char **s)
{
	ft_dprintf(2, "%s: syntax error near unexpected token '%c'\n", SHELL_NAME, **s);
	return (-2);
}

t_token			*tokenize(char *input, long len)
{
	t_token			*head;
	t_token			*token;
	enum e_state	st; // make this var an array if multiple states required
	enum e_signal	sig;
	t_lex_func		do_action;

	if (!input || !len)
		return (0);
	token = 0;
	head = 0;
	st = S_SPECIAL;
	while (*input)
	{
		sig = get_signal(*input);
		if ((do_action = g_fsm_table[st][sig].func) != 0)
			if (do_action(&token, &input) < 0)
			{
				ft_putstr("FAILED TO ALLOCATE TOKEN LIST!!!\n");
				return (0);
			}
		st = g_fsm_table[st][sig].state;
		head = (head == 0 && token != 0) ? token : head;
		input++;
	}
	if (st == S_QUOTE || st == S_DQUOTE)
		ft_dprintf(2, "Quotes does not match!\n");
	return (head);
}

/*
char *type(enum e_signal sig) // for tests
{
	char *type[8] = {
		"GEN ",
		"VARN",
		"EXPR",
		"ESC ",
		"QUO ",
		"DQUO",
		"SPA ",
		"SEMI"
	};
	return (type[sig]);
}

#include <stdio.h>
int	main(int ac, char **av)
{
	t_token *lst;

	if (ac == 2)
		lst = tokenize(av[1], ft_strlen(av[1]));
	else
		return (printf("No input\n"));
ft_printf("passed string: %s\n", av[1]);
ft_printf("lst: %p\n\n", lst);
	while (lst)
	{
		printf(">>> type: %s, data: %s\n", type(lst->type), lst->data);
		lst = lst->next;
	}
	return (0);
}
*/
