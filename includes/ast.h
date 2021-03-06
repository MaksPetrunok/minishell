/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 13:29:29 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 19:11:10 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "minishell.h"

/*
** tree.c
*/
int					execute_tree(t_ast *root);

typedef int			(*t_exec_node)(t_ast *node);

int					pipeline(t_ast *node);
int					logic(t_ast *node);
int					semicolon(t_ast *node);

/*
** exec_pipe.c
*/
int					pipe_recursive(t_ast *node, int *pipe_fd);
int					pipe_to(t_ast *node, int *fd, int *parent_nd);
int					pipe_from(t_ast *node, int *fd);

#endif
