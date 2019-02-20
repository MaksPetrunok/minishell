/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 13:08:57 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/20 13:38:16 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	assign_var(t_ast *node)
{
	ft_printf("Assign var: %s\n", node->left->tkn_lst->data);
	return (0);
}

int	exec_wait(t_ast *node)
{
	ft_printf("Assign var: %s\n", node->left->tkn_lst->data);
	return (0);
}

int	exec_no_wait(t_ast *node)
{
	ft_printf("Assign var: %s\n", node->left->tkn_lst->data);
	return (0);
}
