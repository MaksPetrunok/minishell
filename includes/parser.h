/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:55:03 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 19:04:52 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

enum	e_ntype
{
	COMMAND = 0,
	PIPE = 1,
	AND = 2,
	OR = 3,
	SEMI = 4,
	NEWLINE = 5
};

typedef struct s_ast	t_ast;

struct				s_ast
{
	t_token			*tkn_lst;
	enum e_ntype	type;
	t_ast			*left;
	t_ast			*right;
};

/*
** tree.c
*/
t_ast				*init_tree(t_token *token);
void				free_tree(t_ast *root);

/*
** parser.c
*/
int					build_tree_from(t_ast *node);
t_token				*get_next(enum e_ntype type, t_token *lst);
int					split_node(t_ast *node, t_token *delim);
t_ast				*make_node(enum e_ntype type, t_token *tkn);
t_ast				*parse(t_token *lst);

/*
** util.c
*/
char				*token_to_str(t_token *tkn);
t_token				*skip_token(t_token *tkn);
int					check_cmd(t_token *tkn);
enum e_ntype		type_trans(enum e_tkn_type type);

#endif
