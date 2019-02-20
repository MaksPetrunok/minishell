/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:39:33 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/20 13:55:27 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_exec_node	exec_node[6] =
{
	[COMMAND] = &exec_wait,
	[PIPE] = &pipeline,
	[AND] = &logic,
	[OR] = &logic,
	[SEMI] = &semicolon,
	[NEWLINE] = &semicolon
};

int	execute_tree(t_ast *root)
{
	return (exec_node[root->type](root));
}

void		free_tree(t_ast *root)
{
	if (!root)
		return ;
	ft_printf("Freeing Tree: %p\n", root); //
	ft_printf("        left: %p\n", root->left); //
	ft_printf("       right: %p\n", root->right); //
	if (root->left)
		free_tree(root->left);
	if (root->right)
		free_tree(root->right);
	ft_printf("token: %p\n", root->tkn_lst); // debug
	if (root->tkn_lst)
		ft_printf(" data: %p\n", root->tkn_lst->data); //
	while(root->tkn_lst)
		root->tkn_lst = skip_token(root->tkn_lst);
	free((void *)root);
}
