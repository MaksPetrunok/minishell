/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 19:19:19 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/18 11:52:16 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Syntax:

T_WORD
T_IO_NUM
T_ASSIGN
T_AND
T_OR
T_PIPE
T_AMP
T_NEWLINE
*/

/*
 * Takes a list of tokens as input and returns an executable tree.
 * If input is NULL or there is a syntax error returns NULL.
*/

/*
 * NoTES:
 * |, &&, || operators must have not empty right child node!
*/

t_exec_tree	*parse(t_token *tkn)
{
	t_exec_tree	*root;
	t_exec_tree	*node;

	if (tkn == NULL || (root = init_node(NULL)) == NULL)
		return (NULL);
	node = root;
	while (tkn)
	{
		if (tkn->type == T_IO_NUM &&
			(tkn->next == NULL || tkn->next->type != T_WORD))
		{
			ft_dprintf(2, "syntax error near unexpected token: '%s'\n",
			(tkn->next == NULL) ? "newline" : get_tkn_type(tkn->next->type));
			// free root
			return (NULL);
		}
		if (node->left == NULL)
		{
			// handle T_NEWLINEs properly
			if (tkn->type == T_WORD || tkn->type == T_IO_NUM)
			{
				if ((node->left = init_node(tkn)) == NULL) // create new node with data=current token
				{
					// free root
					return (NULL);
				}
				ft_printf("New left token: %s\n", tkn->data); // debug
			}
			else
			{
				ft_dprintf(2, "syntax error near unexpected token: '%s'\n",
				(tkn->data == NULL) ? get_tkn_type(tkn->type) : tkn->data);
				// use proper token name for error report
				// free memory used by exec_tree
				return (NULL);
			}
		}
		else if (tkn->type != T_WORD && tkn->type != T_IO_NUM && tkn->type != T_PIPE)
		{
			node->tkn = tkn;			// set current node data to tkn
			node->right = init_node(NULL);	// create empty node on right
			node = node->right;			// and make it current node
			tkn->prev->next = NULL;		// break token chain for left node, leave only words and IO_redir.
			ft_printf("Add operator: %d\n", tkn->type);
		}
ft_printf("Adding token: %s\n", tkn->data);
		tkn = tkn->next;
	}
	ft_printf("END PARSING\n-----------------------------------\n"); // debug
	return (root);
}
