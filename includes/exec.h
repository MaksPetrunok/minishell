/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:25:59 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/11 22:22:49 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "parser.h"

/*
** ast.c
*/
int	execute_tree(t_ast *root);

typedef int			(*t_exec_func)(t_ast *node);

/*
** exec_func.c
*/
int					assign_var(t_ast *node);
int					eval_logic(t_ast *node);
int					exec_wait(t_ast *node);
int					exec_no_wait(t_ast *node);

#endif
