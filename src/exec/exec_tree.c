/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:39:33 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/27 17:12:03 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_exec_func	*exec_table[10] =
{
	[T_ASSIGN] = &assign_var,
	[T_AND] = &eval_logic,
	[T_OR] = &eval_logic,
	[T_AMP] = &exec_no_wait,
	[T_NEWLINE] = &exec_wait
}

COMMAND, OPERATOR
execute(char **av, t_env *env)

static int	redirect_and_launch(t_token *lst)
{

}

int	execute_tree(t_exec_tree *root)
{
	t_token	*token;
	int		ret;

	ret = 1;
	if (root == NULL)
		return (-1);
	if ((ret = execute_tree(root->left)) == 0)
		return (ret);
	token = root->tkn;
	if (!token)
		return (ret);
	else if (node->type == COMMAND)
		ret = redirect_and_launch(root->tkn);
	else if (node->type == OPERATOR)
		
	if (token)
		ft_printf("%s ", get_tkn_type(token->type));
	while (token && token->data != NULL)
	{
		ft_printf("%s ", token->data);
		token = token->next;
	}
	ft_printf("\n");
	return (execute_tree(root->right));
}
