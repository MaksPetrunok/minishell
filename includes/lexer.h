/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:25:59 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/30 20:38:38 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include "err.h"

# define TKN_LST_SIZE	3

enum	e_state
{
	S_GENERAL,
	S_EXPR,
	S_ESCAPE,
	S_QUOTE,
	S_DQUOTE,
	S_SPACE,
	S_SPECIAL
};

enum	e_signal
{
	CH_GENERAL,
	CH_VARNAME,
	CH_EXPR,
	CH_ESCAPE,
	CH_QUOTE,
	CH_DQUOTE,
	CH_SPACE,
	CH_SEMICOLON,

	CH_NULL = -1
};

typedef struct s_token	t_token;

struct				s_token
{
	char			*data;
	int				pos;
	int				complete;
	char			type;
	t_token			*next;
};

typedef	int			(*t_lex_func)(t_token **tkn, char **str);

typedef struct		s_state_trans
{
	enum e_state	state;
	t_lex_func		func;
}					t_state_trans;

/*
** Transition functions:
*/

int					new_emp_tkn(t_token **tkn, char **s);
int					new_exp_tkn(t_token **tkn, char **s);
int					append_tkn(t_token **tkn, char **s);
int					add_space(t_token **tkn, char **s);
int					unexpected_tkn(t_token **tkn, char **s);
int					getexp(t_token **tkn, char **s);

/*
** Finite State Machine's state transition table definition.
*/
	
extern t_state_trans	g_fsm_table[7][8];
/*{
	[S_GENERAL][CH_GENERAL] = {S_GENERAL, &append_tkn},
	[S_GENERAL][CH_VARNAME] = {S_GENERAL, &append_tkn},
	[S_GENERAL][CH_EXPR] = {S_EXPR, &new_exp_tkn},
	[S_GENERAL][CH_ESCAPE] = {S_ESCAPE, 0},
	[S_GENERAL][CH_QUOTE] = {S_QUOTE, 0},
	[S_GENERAL][CH_DQUOTE] = {S_DQUOTE, 0},
	[S_GENERAL][CH_SPACE] = {S_SPACE, &add_space},
	[S_GENERAL][CH_SEMICOLON] = {S_SPECIAL, &new_emp_tkn},

	[S_EXPR][CH_GENERAL] = {S_GENERAL, &new_emp_tkn},
	[S_EXPR][CH_VARNAME] = {S_EXPR, &append_tkn},
	[S_EXPR][CH_EXPR] = {S_EXPR, &append_tkn},
	[S_EXPR][CH_ESCAPE] = {S_GENERAL, &new_emp_tkn},
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
	[S_DQUOTE][CH_ESCAPE] = {S_ESCAPE, 0},
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
*/
#endif
