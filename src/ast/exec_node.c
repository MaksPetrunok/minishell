/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:48:04 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/20 13:58:24 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipeline(t_ast *node)
{
	(void)node;

	return (0);
}

int	logic(t_ast *node)
{
	execute_tree(node->left);
	if ((g_shell.last_ret == 0 && node->type == AND) ||
		(g_shell.last_ret != 0 && node->type == OR))
		execute_tree(node->right);
	return (1);
}

int	semicolon(t_ast *node)
{
	if (node->left)
		execute_tree(node->left);
	if (node->right)
		execute_tree(node->right);
	return (1);
}
