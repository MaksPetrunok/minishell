/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 13:08:57 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/28 19:02:30 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(t_ast *node)
{
	t_func	bf;
	char	**av;
	char	**redir_lst;
	int		run;

	redir_lst = NULL;
	run = 1;
	if ((av = get_arg_vector(node->tkn_lst, &redir_lst)) == NULL)
		return (1);
	if ((bf = get_builtin(*av)) != 0)
	{
		if (backup_stdio())
		{
			redirect_io(redir_lst);
			run = bf(av, g_shell.environ);
			restore_stdio();
		}
	}
	else
		run = execute_redir(av, g_shell.environ, redir_lst);
	free((void *)av);
	free((void *)redir_lst);
	return (run);
}

// executes last command in pipeline and waits for result
int	exec_wait_pipe(t_ast *node, int *fd)
{
	pid_t	pid;
	int		status;
	char	**av;
	char	**redir_lst;

	pid = fork();
	if (pid == -1)
		ft_dprintf(2, "error while launching process\n");
	else if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		if ((av = get_arg_vector(node->tkn_lst, &redir_lst)) == NULL)
			exit(1);
		redirect_io(redir_lst);
		launch_process(av, g_shell.environ);
		exit(127);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, &status, 0);
	g_shell.last_ret = WEXITSTATUS(status);

//	ft_printf("WAIT: %s, pid=%d\n", node->tkn_lst->data, getpid());
	return (1);
}

// executes commands in pipeline except last and doesn't wait process
int	exec_no_wait(t_ast *node)
{
	char	**av;
	char	**redir_lst;

//	ft_dprintf(2, "NO WAIT: %s, pid=%d\n", node->tkn_lst->data, getpid());

	if ((av = get_arg_vector(node->tkn_lst, &redir_lst)) == NULL)
		exit(1);
	redirect_io(redir_lst);
	launch_process(av, g_shell.environ);
	exit(127);
}
