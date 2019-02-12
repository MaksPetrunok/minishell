/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:39:33 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/12 22:42:43 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static enum e_ntype	get_node_type(t_token *tkn)
{
	if (tkn != NULL && tkn->type != T_WORD && tkn->type != T_IO_NUM)
		return (COMMAND);
	else
		return (OPERATOR);
}

t_exec_tree	*init_node(t_token *token)
{
	t_exec_tree	*node;

	if ((node = malloc(sizeof(t_exec_tree))) == NULL)
	{
		ft_dprintf(2, "cannot parse input, allocation error\n");
		return (NULL);
	}
	node->left = NULL;
	node->right = NULL;
	node->type = get_node_type(token);
	node->tkn = token;
	return (node);
}

void		free_tree(t_ast *root)
{
	if (root->left)
		free_tree(root->left);
	if (root->right)
		free_tree(root->right);
	free((void *)root);
}
