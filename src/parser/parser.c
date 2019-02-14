/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 19:19:19 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/13 20:43:00 by mpetruno         ###   ########.fr       */
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
T_SEMI

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
static char	*token_to_str(t_token *tkn)
{
	if (tkn->type == T_SEMI)
		return (";");
	else if (tkn->type == T_NEWLINE)
		return ("newline");
	else if (tkn->type == T_PIPE)
		return ("|");
	else if (tkn->type == T_OR)
		return ("||");
	else if (tkn->type == T_AND)
		return ("&&");
	else
		return (tkn->data);
}

t_token	*skip_token(t_token *tkn)
{
	t_token	*tmp;

	tmp = tkn;
	tkn = tkn->next;
	if (tkn)
		tkn->prev = NULL;
	free(tmp->data);
	free(tmp);
	return (tkn);
}


int		check_cmd(t_token *tkn)
{
	while (tkn)
	{
		if (tkn->type == T_IO_NUM &&
			(tkn->next == NULL || tkn->next->type != T_WORD))
		{
			ft_printf("syntax error after token '%s'\n", token_to_str(tkn));
			return (0);
		}
		tkn = (tkn->type == T_IO_NUM) ? tkn->next->next : tkn->next;
	}
	return (1);
}

int		build_tree_from(t_ast *node)
{
	t_token	*delim;
	if (node->tkn_lst == NULL)
		return (1);
	if (node->type == COMMAND)
		return (check_cmd(node->tkn_lst));

	while (node->tkn_lst && node->tkn_lst->type == T_NEWLINE)
		node->tkn_lst = skip_token(node->tkn_lst);
	if ((delim = get_next(node->type, node->tkn_lst)) == NULL)
	{
		node->type--;
		return (build_tree_from(node));
	}
	else if (delim->type == T_NEWLINE && delim->next == NULL)
	{
		delim->prev->next = NULL;
		skip_token(delim);
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
	else if (type == T_SEMI)
		return SEMI;
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

static void	print_tokens(t_token *tkn)
{
	while (tkn)
	{
		char *s = token_to_str(tkn);
		ft_printf("%s ", s);
		tkn=tkn->next;
	}
	ft_putstr("\n");
}

// returns 1 upon successfull subtree creation (recursively)
// returns 0 on error (syntax, allocation, etc)
int		split_node(t_ast *node, t_token *delim)
{
	ft_printf("Before ERROR\n");
	if ((node->tkn_lst == delim && delim->type != T_NEWLINE) ||
		(delim->next == NULL && delim->type != T_NEWLINE && delim->type != T_SEMI))
	{
		ft_dprintf(2, "syntax error near token '%s'\n", token_to_str(delim));
		return (0);
	}
print_tokens(node->tkn_lst);
print_tokens(delim);
ft_printf("%p\n%p\n", node->tkn_lst, delim);
	ft_printf("After ERROR\n");
	if ((node->left = make_node(node->type - 1, node->tkn_lst)) == NULL ||
		(node->right = make_node(node->type, delim->next)) == NULL)
	{
		ft_dprintf(2, "allocation error\n");
		return (0);
	}
	delim->prev->next = NULL;
	delim->next = NULL;
	node->tkn_lst = delim;
ft_printf("NODE: "); print_tokens(node->tkn_lst); //
ft_printf("   L: "); print_tokens(node->left->tkn_lst); //
ft_printf("   R: "); print_tokens(node->right->tkn_lst); //
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
	node->left = NULL;
	node->right = NULL;
	return (node);
}

// returns AST for token list, or NULL on faulure
t_ast	*parse(t_token *lst)
{
	t_ast *root;

	if (!lst || (root = make_node(NEWLINE, lst)) == NULL)
		return (NULL);
	build_tree_from(root);
	return (root);
	/*
	else
	{
		ft_printf("----------- freeing tree on error -------------\n");
		free_tree(root);
		ft_printf("----------- freeing tree on error /-------------\n");
		return (NULL);
	}
	*/
}
