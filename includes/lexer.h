/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:25:59 by mpetruno          #+#    #+#             */
/*   Updated: 2019/01/28 18:37:36 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include "err.h"

enum	e_state
{
	S_GEN,
	S_SQT,
	S_DQT
};

enum	e_signal
{
	CH_GEN,
	CH_NLN,
	CH_ESC,
	CH_SQT,
	CH_DQT,
	CH_EXP,
	CH_IOR,
	CH_LOG,
	CH_WSP
};

enum	e_tkn_type
{
	T_WORD,
	T_IO_NUM,
	T_ASSIGN,
	T_AND,
	T_OR,
	T_NEWLINE
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

enum e_signal		get_signal(char c);
t_token				*init_token(int size);

/*
** FSM transition functions:
*/

// create new token and add current character as first token character
int					tkn_create(t_token **tkn, char **s);
// create T_NEWLINE token
int					tkn_newline(t_token **tkn, char **s);
//add current character to the end of current token
//if **tkn marked as complete (tkn->complete == 1), initiate new token
int					tkn_append(t_token **tkn, char **s);
// depending on curent status opens escape sequense:
// S_GEN : |  &  ;  <  >  (  )  $  `  \  "  '  <space> \t \n #
// S_DQT : $   `   "   \   \t \n
int					tkn_escgen(t_token **tkn, char **s);
int					tkn_escdqt(t_token **tkn, char **s);

// find all characters related to expansion and add them to token
int					tkn_expans(t_token **tkn, char **s);
// find all characters related i/o redirection and add to token
int					tkn_ionumb(t_token **tkn, char **s);
int					tkn_complete(t_token **tkn, char **s);
// check if it is logical operator (&& or ||), pipe(|) or single &
// delimit current tkn, create new corresponding token and delimit it as well
int					tkn_logic(t_token **tkn, char **s);

#endif
