/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:25:59 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 19:06:48 by mpetruno         ###   ########.fr       */
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
	S_DQT,
	S_BQT,
	S_HSH,
	S_HD
};

enum	e_signal
{
	CH_GEN,
	CH_NLN,
	CH_SCL,
	CH_ESC,
	CH_SQT,
	CH_DQT,
	CH_BQT,
	CH_EXP,
	CH_IOR,
	CH_LOG,
	CH_EQU,
	CH_WSP,
	CH_HSH
};

enum	e_tkn_type
{
	T_WORD,
	T_IO_NUM,
	T_ASSIGN,
	T_AND,
	T_OR,
	T_PIPE,
	T_AMP,
	T_SEMI,
	T_NEWLINE
};

typedef struct s_token	t_token;

struct				s_token
{
	char			*data;
	char			*src;
	int				pos;
	int				size;
	int				complete;
	char			type;
	t_token			*prev;
	t_token			*next;
};

typedef	int			(*t_lex_func)(t_token **tkn, char **str);

typedef struct		s_state_trans
{
	enum e_state	state;
	t_lex_func		func;
}					t_state_trans;

t_token				*tokenize(char *s);

t_token				*init_token(int size, t_token *prev);
char				*get_tkn_type(enum e_tkn_type type);

/*
** Aux functions for opening expansions.
*/
int					tkn_escgen(t_token **tkn, char **s);
int					tkn_escdqt(t_token **tkn, char **s);

/*
** heredoc.c
*/
int					open_heredocs(t_token *lst);

/*
** FSM transition functions:
*/
int					tkn_create(t_token **tkn, char **s);
int					tkn_newline(t_token **tkn, char **s);
int					tkn_append(t_token **tkn, char **s);
int					tkn_escape(t_token **tkn, char **s);
int					tkn_expans(t_token **tkn, char **s);
int					tkn_ionumb(t_token **tkn, char **s);
int					tkn_complete(t_token **tkn, char **s);
int					tkn_logic(t_token **tkn, char **s);
int					tkn_assign(t_token **tkn, char **s);

#endif
