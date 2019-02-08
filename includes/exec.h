/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:25:59 by mpetruno          #+#    #+#             */
/*   Updated: 2019/01/30 19:01:27 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "lexer.h"

enum	e_ntype
{
	COMMAND,
	OPERATOR
};

typedef struct s_exec_tree	t_exec_tree;

struct				s_exec_tree
{
	t_token			*tkn;
	enum e_ntype	type;
	t_exec_tree		*left;
	t_exec_tree		*right;
};

/*
** tree.c
*/
t_exec_tree			*init_node(t_token *token);
void				free_tree(t_exec_tree *root);

/*
** exec_tree.c
*/
int	execute_tree(t_exec_tree *root);

typedef int			(*t_exec_func)(t_exec_tree *node);

/*
** exec_func.c
*/
int					assign_var(t_exec_tree *node);
int					eval_logic(t_exec_tree *node);
int					exec_wait(t_exec_tree *node);
int					exec_no_wait(t_exec_tree *node);

#endif
