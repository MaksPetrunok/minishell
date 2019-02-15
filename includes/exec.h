/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:25:59 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/15 16:56:36 by mpetruno         ###   ########.fr       */
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
** tkn_add.c
*/
int					tkn_add(t_token **tkn, char **inp);

/*
** expansion.c
*/
int					expand_token(t_token *tkn);

/*
** expand_str.c
*/
int					expand_str(t_token **tkn, char **input);

/*
** exec_func.c
*/
int					assign_var(t_ast *node);
int					eval_logic(t_ast *node);
int					exec_wait(t_ast *node);
int					exec_no_wait(t_ast *node);

#endif
