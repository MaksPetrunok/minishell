/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:39:33 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 19:02:35 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_exec_node	g_exec_node[6] =
{
	[COMMAND] = &exec_cmd,
	[PIPE] = &pipeline,
	[AND] = &logic,
	[OR] = &logic,
	[SEMI] = &semicolon,
	[NEWLINE] = &semicolon
};

int		execute_tree(t_ast *root)
{
	return (g_exec_node[root->type](root));
}

void	free_tree(t_ast *root)
{
	if (!root)
		return ;
	if (root->left)
		free_tree(root->left);
	if (root->right)
		free_tree(root->right);
	while (root->tkn_lst)
		root->tkn_lst = skip_token(root->tkn_lst);
	free((void *)root);
}
