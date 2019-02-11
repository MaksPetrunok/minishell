/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 19:19:19 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/11 22:44:03 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Syntax:

T_WORD
T_IO_NUM
T_ASSIGN
T_AND
T_OR
T_PIPE
T_AMP
T_NEWLINE

ALGORYTHM DESCRIPTION:

init ast(t_token *tkn):	1. create empty node, set tkn as token list for this node
						2. mark node as T_NEWLINE type

// parsing specific node
build_tree_from(
		t_ast *node):	1. if (delim = g_et_next(this.type, this.tkn_lst)) == NULL
						   {
							   set_next_type(node) // reduce type to next value or command
							   build_tree_from(this);
						   }
							else
								split_node(this, delim)

t_token get_next(
	e_tkn_type type,
	t_token *tkn_lst):	1. read tokens from tkn_lst
							- if token with type=type found, return tkn pointer
							- else return NULL

// create child nodes separated by operator
split_node(t_ast node,
		t_token tkn):	1. if node->tkn_list == tkn (no tokens before tkn in node)
						   or tkn->next == NULL (no tokens after tkn):
							print "Syntax error!"
						2. create left and right child nodes
						3. set token list from this node to left child, delimit before tkn
						4. set tkn->next to right child
						5. set this node type as tkn->type
							- build_tree_from(left)
							- build_tree_from(right)
*/

int		build_tree_from(t_ast *node)
{
	t_token	*delim;

	if (node->type == COMMAND)
		return (1);
	if ((delim = get_next(node->type, node->tkn_lst)) == NULL)
	{
		node->type--;
		return (build_tree_from(node));
	}
	else
		return (split_node(node, delim));
}


static enum e_ntype	type_trans(enum e_tkn_type type)
{
	if (type == T_NEWLINE)
		return NEWLINE;
   else if (type == T_OR)
		return OR;
   else if (type == T_AND)
		return AND;
   else if (type == T_PIPE)
		return PIPE;
   else
		return COMMAND;
}

t_token	*get_next(enum e_ntype type, t_token *lst)
{
	while (lst && type_trans(lst->type) != type)
		lst = lst->next;
	return (lst);
}

// returns 1 upon successfull subtree creation (recursively)
// returns 0 on error (syntax, allocation, etc)
int		split_node(t_ast *node, t_token *delim)
{
	//handle multiple newline tokens
	if ((node->tkn_lst == delim || delim->next == NULL) && delim->type != T_NEWLINE)
	{
		ft_dprintf(2, "syntax error near token '%d', two operands expected\n", delim->type);
		return (0);
	}
	//if (!tokens || tokens->type == T_NEWLINE)
	//	return (NULL);
	// check conditions here and assign NULL to child nodes if required
	if ((node->left = make_node(node->type - 1, node->tkn_lst)) == NULL ||
		(node->right = make_node(node->type, delim->next)) == NULL)
	{
		ft_dprintf(2, "allocation error\n");
		return (0);
	}
	delim->prev->next = NULL;
	// free node properly !!!!!!!!!!!!!!! IMPORTANT !!!
	return (build_tree_from(node->left) &&
			build_tree_from(node->right));
}

// create AST node of type 'type' and tkn_lst=tokens, child nodes eq. NULL
t_ast	*make_node(enum e_ntype type, t_token *tokens)
{
	t_ast	*node;

	if ((node = malloc(sizeof(t_ast))) == NULL)
	{
		ft_dprintf(2, "allocation error\n");
		return (NULL);
	}
	node->tkn_lst = tokens;
	node->type = type;
	return (node);
}

// returns AST for token list, or NULL on faulure
t_ast	*parse(t_token *lst)
{
	t_ast *root;

	if (!lst ||
		(root = make_node(NEWLINE, lst)) == NULL)
		return (NULL);
	if (build_tree_from(root))
		return (root);
	else
	{
		//free_tree(root); write implementation
		return (NULL);
	}
}
