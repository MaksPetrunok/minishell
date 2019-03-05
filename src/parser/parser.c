/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 19:19:19 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 17:19:31 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	{
		node->type = type_trans(delim->type);
		return (split_node(node, delim));
	}
}

t_token	*get_next(enum e_ntype type, t_token *lst)
{
	t_token	*delim;

	delim = NULL;
	while (lst)
	{
		if (type_trans(lst->type) == type ||
			((lst->type == T_OR || lst->type == T_AND) &&
			(type == OR || type == AND)))
			delim = lst;
		lst = lst->next;
	}
	return (delim);
}

int		split_node(t_ast *node, t_token *delim)
{
	if ((node->tkn_lst == delim && delim->type != T_NEWLINE) ||
		(delim->next == NULL &&
		delim->type != T_NEWLINE && delim->type != T_SEMI))
	{
		ft_dprintf(2, "syntax error near token '%s'\n", token_to_str(delim));
		return (0);
	}
	if ((node->left = make_node(node->type, node->tkn_lst)) == NULL ||
		(node->right = make_node(node->type - 1, delim->next)) == NULL)
	{
		ft_dprintf(2, "allocation error\n");
		return (0);
	}
	delim->prev->next = NULL;
	delim->next = NULL;
	node->tkn_lst = delim;
	return (build_tree_from(node->left) &&
			build_tree_from(node->right));
}

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

t_ast	*parse(t_token *lst)
{
	t_ast *root;

	if (!lst || (root = make_node(NEWLINE, lst)) == NULL)
		return (NULL);
	if (build_tree_from(root))
		return (root);
	else
	{
		free_tree(root);
		return (NULL);
	}
}
