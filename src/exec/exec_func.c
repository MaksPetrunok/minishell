/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:39:33 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/27 17:12:03 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	assign_var(t_exec_tree *node)
{
	ft_printf("Assign var: %s\n", node->left->tkn->data);
	return (0);
}

int	eval_logic(t_exec_tree *node)
{
	ft_printf("Assign var: %s\n", node->left->tkn->data);
	return (0);
}

int	exec_wait(t_exec_tree *node)
{
	ft_printf("Assign var: %s\n", node->left->tkn->data);
	return (0);
}

int	exec_no_wait(t_exec_tree *node)
{
	ft_printf("Assign var: %s\n", node->left->tkn->data);
	return (0);
}
