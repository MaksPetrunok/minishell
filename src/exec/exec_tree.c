/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:39:33 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/11 22:27:13 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	execute_tree(t_ast *root)
{
	if (root->type == COMMAND)
	{
		ft_printf("COMMAND: ");
		while (root->tkn_lst)
		{
			ft_putstr(root->tkn_lst->data);
			ft_putstr(" ");
			root->tkn_lst = root->tkn_lst->next;
		}
		ft_putstr("\n");
		return (1);
	}
	execute_tree(root->left);
	char *s;
	switch (root->type) {
		case AND: s = "&&"; break;
		case OR:  s = "||"; break;
		case PIPE: s = "|"; break;
		case NEWLINE: s = ";"; break;
		default: s = "What the helL?";
	}
	ft_printf("%s\n", s);
	execute_tree(root->right);
	return (0);
}
