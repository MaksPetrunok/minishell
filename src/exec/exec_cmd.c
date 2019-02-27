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
/*
1. get_arg_vector(redir)
	expand_tokens
	accomplish assignments
	returns vector of command and command arguments only
	writes required redirections to redir
2. if get_arg_vector returned NULL as command vector - free redir and return
3. if *av - builtin:
	- duplicate fds 0, 1, 2
	- perform redirection
	- execute builtin
	-restore fds 0,1,2

4. if *av - not builtin:
	- fork new process
	- perform redirections
	- execve new process

env: if command is builtin - run builtin
		else fork run specific command, closing stdio duplicate fds
	
	
*/

	t_func	bf;
	char	**av;
	char	**redir_lst;
	int		res;

	redir_lst = NULL;
	if ((av = get_arg_vector(node->tkn_lst, &redir_lst)) == NULL || *av == NULL)
	{
		free((void *)av);
		free((void *)redir_lst);
		return (1);
	}
/*
for(int i=0; av[i] != NULL; i++)
ft_printf("av[%d] = %s\n", i, av[i]);
for(int i=0; redir_lst[i] != NULL; i++)
ft_printf("redir[%d] = %s\n", i, redir_lst[i]);
*/
	if ((bf = get_builtin(*av)) != 0)
	{
		if (backup_stdio())
		{
			redirect_io(redir_lst);
			res = bf(av);
			restore_stdio();
		}
	}
	else
		res = execute_redir(av, g_shell.environ, redir_lst);
	free((void *)av);
	free((void *)redir_lst);
	return (res);
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
