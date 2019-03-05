/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:48:04 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 18:58:32 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipeline(t_ast *node)
{
	int	fd[2];

	pipe(fd);
	if (node->left->type == PIPE)
		pipe_recursive(node->left, fd);
	else
		pipe_from(node->left, fd);
	exec_wait_pipe(node->right, fd);
	return (1);
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
	if (node->right && node->right->tkn_lst)
		execute_tree(node->right);
	return (1);
}
