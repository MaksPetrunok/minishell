/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:55:03 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/11 22:16:14 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "lexer.h"

enum	e_ntype
{
	COMMAND = 0,
	PIPE = 1,
	AND = 2,
	OR = 3,
	NEWLINE = 4
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
** node.c
*/
// try to build tree starting from node
// if successfull - return 1, else return 0
int					build_tree_from(t_ast *node);
// return pointer to the next token of type 'type' in lst
// if not found return NULL
t_token				*get_next(enum e_ntype type, t_token *lst);
// create two child nodes for current node,
// assign corresponding token lists to them,
// parse each cild node recursively
// on success return 1, otherwise 0
int					split_node(t_ast *node, t_token *delim);
// create t_ast node and assign tkn list to it
t_ast				*make_node(enum e_ntype type, t_token *tkn);

t_ast				*parse(t_token *lst);


#endif
