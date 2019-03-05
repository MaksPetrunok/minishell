/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 12:48:04 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 18:57:20 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_from(t_ast *node, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_dprintf(2, "error while launching process\n");
	else if (pid > 0)
	{
		close(fd[1]);
		return ((int)pid);
	}
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	g_shell.is_fork = 1;
	exec_no_wait(node);
	exit(0);
	return (1);
}

int	pipe_to(t_ast *node, int *fd, int *parent_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_dprintf(2, "error while launching process\n");
	else if (pid > 0)
	{
		close(fd[0]);
		close(parent_fd[1]);
		return ((int)pid);
	}
	close(fd[1]);
	close(parent_fd[0]);
	dup2(fd[0], 0);
	dup2(parent_fd[1], 1);
	close(fd[0]);
	close(parent_fd[1]);
	g_shell.is_fork = 1;
	exec_no_wait(node);
	exit(0);
	return (1);
}

int	pipe_recursive(t_ast *node, int *pipe_fd)
{
	int	fd[2];

	pipe(fd);
	if (node->left->type == PIPE)
		pipe_recursive(node->left, fd);
	else
		pipe_from(node->left, fd);
	pipe_to(node->right, fd, pipe_fd);
	return (1);
}
