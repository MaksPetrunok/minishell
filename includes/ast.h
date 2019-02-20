/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 13:29:29 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/20 13:32:31 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

#include "minishell.h"

/*
** tree.c
*/
int	execute_tree(t_ast *root);

typedef int			(*t_exec_node)(t_ast *node);

int					pipeline(t_ast *node);
int					log_and(t_ast *node);
int					log_or(t_ast *node);
int					semicolon(t_ast *node);

#endif
