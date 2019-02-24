/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 13:08:57 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/21 20:14:25 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(t_ast *node)
{
	(void)node;
/*
1. Check if builtin should be executed:
- if yes:
	make copy of fds 0, 1, 2 using dup()
	perform redirections
- if no:

*/ 	
	return (0);
}

int	exec_wait_pipe(t_ast *node, int *fd)
{
	pid_t	pid;
	int		status;
	char	**av;

	pid = fork();
	if (pid == -1)
		ft_dprintf(2, "error while launching process\n");
	else if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		av = get_arg_vector(node->tkn_lst);
		if (av && *av)
			launch_process(av, g_shell.environ);
		exit(127);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, &status, 0);
	g_shell.last_ret = WEXITSTATUS(status);

//	ft_printf("WAIT: %s, pid=%d\n", node->tkn_lst->data, getpid());
	return (0);
}

int	exec_no_wait(t_ast *node)
{
	char	**av;

//	ft_dprintf(2, "NO WAIT: %s, pid=%d\n", node->tkn_lst->data, getpid());
	av = get_arg_vector(node->tkn_lst);
	if (av && *av)
		launch_process(av, g_shell.environ);
	exit(0);
	return (0);
}
