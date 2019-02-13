/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:39:33 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/13 18:11:36 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	execute_tree(t_ast *root)
{
	char *type;
	switch (root->type) {
		case COMMAND: type = "Command"; break;
		case NEWLINE: type = "NewLine"; break;
		case OR:      type = "OR     "; break;
		case AND:     type = "AND    "; break;
		case PIPE:    type = "Pipe   "; break;
		default:      type = "Unknown type";
	}
	if (root->type == COMMAND)
	{
		ft_printf("%s:", type);
		while (root->tkn_lst)
		{
			ft_putstr(" ");
			ft_putstr(root->tkn_lst->data);
			root->tkn_lst = root->tkn_lst->next;
		}
		ft_putstr("\n");
		return (1); //
	}
	else
	{
		if (root->left)
			execute_tree(root->left);
		ft_printf("%s:", type);
		char *s;
		switch (root->type) {
			case AND: s = "&&"; break;
			case OR:  s = "||"; break;
			case PIPE: s = "|"; break;
			case NEWLINE: s = ";"; break;
			default: s = "What the helL?";
		}
		ft_printf(" %s\n", s);
		if (root->right)
			execute_tree(root->right);
	}
	return (0);
}
