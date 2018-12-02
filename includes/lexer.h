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

enum e_signal		get_signal(char c);
t_token				*init_token(int size);

/*
** FSM transition functions:
*/

int					new_emp_tkn(t_token **tkn, char **s);
int					append_tkn(t_token **tkn, char **s);
int					add_space(t_token **tkn, char **s);
int					unexpected_tkn(t_token **tkn, char **s);
int					getexp(t_token **tkn, char **s);
int					escape(t_token **tkn, char **s);

#endif
