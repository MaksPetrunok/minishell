/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:39:33 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/30 21:45:55 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// BEFORE RELEASE:
// Make output buffer in ft_printf from static to dynamic.
// Instead of flushing buffer to fd when it's full - reallocate new buffer
// and copy old buffer to new, continue filling increased buffer.
// Output should be printed only one time.
// Think about flushing the buffer when its size reaches some value, i.e. 10kB.

#include "minishell.h"

pid_t	g_child;

int		is_executable(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (0);
	if (S_ISREG(st.st_mode) && (S_IXUSR & st.st_mode))
		return (1);
	return (0);
}

char	*get_exec_path(const char *name)
{
	char	*ret;
	char	*path;
	char	**dirs;

	if (*name == '/' ||
		ft_strstr(name, "./") == name || ft_strstr(name, "../") == name)
	{
		if ((ret = ft_strdup(name)) != 0)
			return (is_executable(ret) ? ret : 0);
		else
		{
			report_error(ERR_MALLOC);
			return (0);
		}
	}
	if ((path = get_var("PATH")) == 0) /////// here
	{
		return (0);
	}
	dirs = tokenize_split(path, ":");
	while (*dirs)
	{
		ret = ft_strjoin3(*dirs, "/", name);
		if (is_executable(ret))
		{
			free((void *)path);
			return (ret); 
		}
		free((void *)ret);
		dirs++;
	}
	free((void *)path);
	return (0);
}

int	execute(char **av)
{
	pid_t	child;
	int		status;
	int		launch;
	char	*cmd;

	child = fork();
	if (child > 0)
		g_child = child;
	if (child == -1)
	{
		ft_dprintf(2, "%s: failed to launch new process '%s'\n", SHELL_NAME, av[0]);
		return (-1);
	}
	else if (child == 0)
	{
//check for leaks in child process
		cmd = get_exec_path(av[0]);
		launch = 0;
		if (cmd)
			launch = execve(cmd, av, get_env());
		else
			ft_dprintf(2, "%s: command not found\n", av[0]);
		if (launch == -1)
			ft_dprintf(2, "%s: %s: Failed to launch the command\n", SHELL_NAME, av[0]);
		free((void*)av);
		free((void *)cmd);
//		ft_dprintf(2, "Failed to launch process '%s', status: %d\n", av[0], launch);
		exit(1);
	}
	status = 1;
	if (waitpid(child, &status, 0) != child)
		ft_dprintf(2, "Error during waiting child pid %d\n", child);
	g_child = 0;
	return (1);
}
