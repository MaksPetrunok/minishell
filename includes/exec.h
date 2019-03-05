/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:25:59 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 19:09:38 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "parser.h"

/*
** execute.c
*/
void				launch_process(char **av, t_env *env);
int					execute(char **av, t_env *env);
int					execute_redir(char **av, t_env *env, char **io);

/*
** tkn_add.c
*/
int					tkn_add(t_token **tkn, char **inp);

/*
** expansion.c
*/
void				expand_tokens(t_token *tkn);

/*
** expand_str.c
*/
int					expand_str(t_token **tkn, char **input);

/*
** get_argv.c
*/
char				**get_arg_vector(t_token *lst, char ***redir_lst);

/*
** redirect.c
*/
void				redirect_io(char **io);

/*
** io_backup.c
*/
int					backup_stdio(void);
void				restore_stdio(void);

/*
** exec_func.c
*/
int					exec_cmd(t_ast *node);
int					eval_logic(t_ast *node);
int					exec_wait_pipe(t_ast *node, int *fd);
int					exec_no_wait(t_ast *node);

#endif
