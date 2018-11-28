/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:25:59 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/28 23:13:53 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <unistd.h> //remove if libft usded
# include <stdlib.h>
# include "libft.h"
# include "err.h"

# define TKN_LST_SIZE	3
# define TKN_WRD_SIZE	10

enum	e_state
{
	S_GENERAL,
	S_ESCAPE,
	S_QUOTE,
	S_DQUOTE
};

enum	e_signal
{
	CH_GENERAL,
	CH_ESCAPE,
	CH_QUOTE,
	CH_DQUOTE,
	CH_SPACE,
	CH_SEMICOLON
};

typedef struct s_token	t_token;

struct		s_token
{
	char	**av;
	int		v_size;
	int 	a_size;
	int		pos;
	short	a_id;
	short	type;
	t_token	*next;
};

typedef	void	(*t_lex_func)(t_token **tkn, char **str);

typedef struct	s_state_trans
{
	enum e_state	state;
	t_lex_func		func;
}				t_state_trans;

/* Transition functions: */
void	general(t_token **tkn, char **s);
void	escape(t_token **tkn, char **s);

/*
 * Finite State Machine's state transition table definition.
 */

t_state_trans	g_fsm_table[4][6] =
{
	[S_GENERAL][CH_GENERAL] = {S_GENERAL, &general},
	[S_GENERAL][CH_ESCAPE] = {S_ESCAPE, 0},
	[S_GENERAL][CH_QUOTE] = {S_QUOTE, 0},
	[S_GENERAL][CH_DQUOTE] = {S_DQUOTE, 0},
	[S_GENERAL][CH_SPACE] = {S_GENERAL, 0},
	[S_GENERAL][CH_SEMICOLON] = {S_GENERAL, 0},

	[S_ESCAPE][CH_GENERAL] = {S_GENERAL, 0},
	[S_ESCAPE][CH_ESCAPE] = {S_GENERAL, &escape},
	[S_ESCAPE][CH_QUOTE] = {S_GENERAL, &escape},
	[S_ESCAPE][CH_DQUOTE] = {S_GENERAL, &escape},
	[S_ESCAPE][CH_SPACE] = {S_GENERAL, &escape},
	[S_ESCAPE][CH_SEMICOLON] = {S_GENERAL, &escape},

	[S_QUOTE][CH_GENERAL] = {S_QUOTE, 0},
	[S_QUOTE][CH_ESCAPE] = {S_QUOTE, 0},
	[S_QUOTE][CH_QUOTE] = {S_GENERAL, 0},
	[S_QUOTE][CH_DQUOTE] = {S_QUOTE, 0},
	[S_QUOTE][CH_SPACE] = {S_QUOTE, 0},
	[S_QUOTE][CH_SEMICOLON] = {S_QUOTE, 0},

	[S_DQUOTE][CH_GENERAL] = {S_DQUOTE, 0},
	[S_DQUOTE][CH_ESCAPE] = {S_DQUOTE, 0},
	[S_DQUOTE][CH_QUOTE] = {S_DQUOTE, 0},
	[S_DQUOTE][CH_DQUOTE] = {S_GENERAL, 0},
	[S_DQUOTE][CH_SPACE] = {S_DQUOTE, 0},
	[S_DQUOTE][CH_SEMICOLON] = {S_DQUOTE, 0}
};

/*
enum e_state	g_fsm_table[4][6] =
{
	[S_GENERAL][CH_GENERAL] = S_GENERAL,
	[S_GENERAL][CH_ESCAPE] = S_ESCAPE,
	[S_GENERAL][CH_QUOTE] = S_QUOTE,
	[S_GENERAL][CH_DQUOTE] = S_DQUOTE,
	[S_GENERAL][CH_SPACE] = S_GENERAL,
	[S_GENERAL][CH_SEMICOLON] = S_GENERAL,

	[S_ESCAPE][CH_GENERAL] = S_GENERAL,
	[S_ESCAPE][CH_ESCAPE] = S_GENERAL,
	[S_ESCAPE][CH_QUOTE] = S_GENERAL,
	[S_ESCAPE][CH_DQUOTE] = S_GENERAL,
	[S_ESCAPE][CH_SPACE] = S_GENERAL,
	[S_ESCAPE][CH_SEMICOLON] = S_GENERAL,

	[S_QUOTE][CH_GENERAL] = S_QUOTE,
	[S_QUOTE][CH_ESCAPE] = S_QUOTE,
	[S_QUOTE][CH_QUOTE] = S_GENERAL,
	[S_QUOTE][CH_DQUOTE] = S_QUOTE,
	[S_QUOTE][CH_SPACE] = S_QUOTE,
	[S_QUOTE][CH_SEMICOLON] = S_QUOTE,

	[S_DQUOTE][CH_GENERAL] = S_DQUOTE,
	[S_DQUOTE][CH_ESCAPE] = S_DQUOTE,
	[S_DQUOTE][CH_QUOTE] = S_DQUOTE,
	[S_DQUOTE][CH_DQUOTE] = S_GENERAL,
	[S_DQUOTE][CH_SPACE] = S_DQUOTE,
	[S_DQUOTE][CH_SEMICOLON] = S_DQUOTE
};
*/
#endif
