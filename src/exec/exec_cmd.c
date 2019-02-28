/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 13:08:57 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/28 16:56:48 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	backup_stdio(void)
{
	g_shell.io_backup[0] = dup(0);
	g_shell.io_backup[1] = dup(1);
	g_shell.io_backup[2] = dup(2);
	if (g_shell.io_backup[0] == -1 ||
		g_shell.io_backup[1] == -1 ||
		g_shell.io_backup[2] == -1)
	{
		ft_dprintf(2, "cannot backup stdio file descriptors\n");
		close(g_shell.io_backup[0]);
		close(g_shell.io_backup[1]);
		close(g_shell.io_backup[2]);
		g_shell.io_backup[0] = -1;
		g_shell.io_backup[1] = -1;
		g_shell.io_backup[2] = -1;
		return (0);
	}
	return (1);
}

static void	restore_stdio(void)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (g_shell.io_backup[i] != -1)
		{
			dup2(g_shell.io_backup[i], i);
			close(g_shell.io_backup[i]);
			g_shell.io_backup[i] = -1;
		}
		i++;
	}
}

// executes single command (without pipeline)
int	exec_cmd(t_ast *node)
{
	t_func	bf;
	char	**av;
	char	**redir_lst;
	int		run;

	redir_lst = NULL;
	run = 1;
	if ((av = get_arg_vector(node->tkn_lst, &redir_lst)) == NULL)
		return (0);
	if ((bf = get_builtin(*av)) != 0)
	{
		if (backup_stdio())
		{
			redirect_io(redir_lst);
			run = bf(av);
			restore_stdio();
		}
	}
	else
		run = execute_redir(av, g_shell.environ, redir_lst);
	free((void *)av);
	free((void *)redir_lst);
	return (run);
}

int	exec_wait_pipe(t_ast *node, int *fd)
{
	(void)node;
	(void)fd;
	return 0;
}
int	exec_no_wait(t_ast *node)
{
	(void)node;
	return 0;
}
/*
// executes last command in pipeline and waits for result
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

// executes commands in pipeline except last and doesn't wait process
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
*/
