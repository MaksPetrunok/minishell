/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:26:31 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/28 23:16:00 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

enum e_signal   get_signal(char c)
{
	if (c == '\\')
		return (CH_ESCAPE);
	else if (c == '\'')
		return (CH_QUOTE);
	else if (c == '\"')
		return (CH_DQUOTE);
	else if (c == '$')
		return (CH_EXPR);
	else if (c == '~')
		return (CH_HOME);
	else if (c == ' ' || c == '\t')
		return (CH_SPACE);
	else if (c == ';')
		return (CH_SEMICOLON);
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
	tkn->type = -1;
	tkn->next = 0;
	return (tkn);
}
/*
int		new_tkn(t_token **tkn, char **s)
{
	t_token	*new;

	if ((new = init_token(
		(get_signal(**s) != CH_SEMICOLON) ? ft_strlen(*s) : 2)) == 0)
		return (-1);
	if (get_signal(**s) == CH_ESCAPE)
		new->data[new->pos] = '\0';
	else
	{
		new->data[new->pos++] = **s;
		new->data[new->pos] = '\0';
		new->type = get_signal(**s);
	}
	if (*tkn == 0)
		*tkn = new;
	else
	{
		(*tkn)->next = new;
		*tkn = new;
	}
	return (0);
}
*/
int		new_tkn(t_token **tkn, char **s)
{
	return (new_emp_tkn(tkn, s));
}

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
		(sig == CH_SEMICOLON || sig == CH_HOME) ? 2 : ft_strlen(*s))) == 0)
		return (-1);
	if (sig == CH_EXPR || sig == CH_HOME)
		new->type = sig;
	else
		new->type = CH_GENERAL;
	if (sig == CH_GENERAL)
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

static int	is_name(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int		getexp(t_token **tkn, char **s)
{
	t_token	*new;
	int		isname;

	if (*(++(*s)) == '\0')
		return (0);
	if ((new = init_token(ft_strlen(*s))) == 0)
		return (-1);
	new->type = CH_EXPR;
	isname = is_name(**s);
	if (!isname && **s != '{')
	{
//		tkn_free(new);
		return (0);
	}
	while (**s)
	{
		if (isname ? !is_name(**s) : **s == '}')
		{
			*s = (**s == ' ' || **s == '\t') ? *s -1 : *s;
			if (*tkn == 0)
				*tkn = new;
			else
			{
				(*tkn)->next = new;
				*tkn = new;
			}

			return (0);
		}
		new->data[new->pos++] = *(*s)++;
		new->data[new->pos] = '\0';
	}
	*s = (**s == 0) ? *s - 1 : *s; 
	if (*tkn == 0)
		*tkn = new;
	else
	{
		(*tkn)->next = new;
		*tkn = new;
	}
	return (0);
}

int		add_space(t_token **tkn, char **s)
{
//	if ((*tkn)->type == -1)
//		(*tkn)->type = get_signal(**s);
	(*tkn)->data[(*tkn)->pos++] = '\n';
	(*tkn)->data[(*tkn)->pos] = '\0';
	return (0);
}

#define SHELL_NAME "SHELL"
int		unexpected_tkn(t_token **tkn, char **s)
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
		ft_printf("Quotes does not match!\n");
	return (head);
}

char *type(enum e_signal sig) // for tests
{
	char *type[8] = {
		"GEN ",
		"EXPR",
		"HOME",
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
