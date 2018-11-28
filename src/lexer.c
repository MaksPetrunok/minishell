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

enum e_signal	get_signal(char c)
{
	if (c == '\\')
		return (CH_ESCAPE);
	else if (c == '\'')
		return (CH_QUOTE);
	else if (c == '\"')
		return (CH_DQUOTE);
	else if (c == ' ')
		return (CH_SPACE);
	else if (c == ';')
		return (CH_SEMICOLON);
	else
		return (CH_GENERAL);
}

t_token			*init_token(void)
{
	t_token	*tkn;
	char	**arg;
	char	*word;

	tkn = malloc(sizeof(t_token));
	arg = malloc(sizeof(char **) * TKN_LST_SIZE);
	word = malloc(TKN_WRD_SIZE);
	if (!(tkn && arg && word))
	{
//		report_error(ERR_MALLOC); //uncomment for using with minishell
		free((void *)tkn);
		free((void *)arg);
		free((void *)word);
		return (0);
	}
	word[0] = '\0';
	arg[0] = word;
	arg[1] = 0;
	tkn->av = arg;
	tkn->v_size = TKN_LST_SIZE;
	tkn->a_size = TKN_WRD_SIZE;
	tkn->pos = 0;
	tkn->a_id = 0;
	tkn->type = 0;
	tkn->next = 0;
	return (tkn);
}

// MOVE THESE FUNCTIONS TO SEPARATE FILE

void	append(t_token **tkn, char **s)
{
	if ((*tkn)->type == 0)
		*tkn->type = get_signal(**s);
//work here
	(*tkn)->av[(*tkn)->a_id]
}

void	general(t_token **tkn, char **s)
{
	if (tkn)
	{
		ft_putchar(**s);
		ft_putstr(" - ");
		ft_putstr("general\n");
	}
}

void	escape(t_token **tkn, char **s)
{
	if (tkn)
	{
		ft_putchar(**s);
		ft_putstr(" - ");
		ft_putstr("escape\n");
	}
}

t_token			*tokenize(char *input, long len)
{
	t_token			*head;
	t_token			*token;
	enum e_state	st; // make this var an array if multiple states required
	enum e_signal	sig;
	t_lex_func		do_action;
   
	if (!input || !len || !(head = init_token()))
		return (0);	
	token = head;
	st = S_GENERAL;
	while (*input)
	{
		sig = get_signal(*input);
		if ((do_action = g_fsm_table[st][sig].func) != 0)
			do_action(&token, &input);
		st = g_fsm_table[st][sig].state;
		input++;
	}
	return (head);
}

int	main(int ac, char **av)
{
	if (ac == 2)
		tokenize(av[1], ft_strlen(av[1]));
	else
		ft_putstr("No input\n");
	return (0);
}
