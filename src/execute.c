/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:39:33 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/05 12:07:00 by mpetruno         ###   ########.fr       */
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

static char	**tokenize_split(char *s, char *delim)
{
	char	**tokens = malloc(sizeof(char **) * 10);
	int		i;
	int		state;

	i = 0;
	state = 0;
	while (*s)
	{
		if (ft_strchr(delim, *s) == 0)
		{
			if (!state)
				tokens[i++] = s;
			state = 1;
		}
		else
		{
			if (state)
				*s = '\0';
			state = 0;
		}
		s++;
	}
	tokens[i] = 0;
	return (tokens);
}

static char	*search_path(const char *name, char *path)
{
	char	**dirs;
	char	*ret;

	dirs = tokenize_split(path, ":");
	while (*dirs)
	{
		if ((ret = ft_strjoin3(*dirs, "/", name)) == 0)
		{
			dirs++;
			continue ;
		}
		if (access(ret, F_OK) == 0)
			return (ret);
		free((void *)ret);
		dirs++;
	}
	return (0);
}

static char	*get_exec_path(const char *name)
{
	char	*ret;
	char	*path;

	if (*name == '/' ||
		ft_strstr(name, "./") == name || ft_strstr(name, "../") == name)
	{
		if ((ret = ft_strdup(name)) == 0)
			return (0);
		if (access(ret, F_OK) == 0)
			return (ret);
		free((void *)ret);
		return (0);
	}
	path = get_var("PATH");
	if (!path || !(*path))
		return (0);
	if ((path = ft_strdup(path)) == 0)
		return (0);
	ret = search_path(name, path);
	free((void *)path);
	return (ret);
}

static void	launch_process(char **av)
{
	char	*cmd;

	cmd = get_exec_path(av[0]);
	if (cmd && av[0][0])
	{
		if (access(cmd, X_OK) == 0)
		{
			execve(cmd, av, get_env());
			ft_dprintf(2, "%s: %s: Failed to launch the command\n", SHELL_NAME, av[0]);
		}
		else
			ft_dprintf(2, "%s: %s: access denied\n", SHELL_NAME, cmd);
	}
	else
		ft_dprintf(2, "%s: %s: command not found\n", SHELL_NAME, *av);
}

int			execute(char **av)
{
	pid_t	child;
	int		status;

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
		launch_process(av);
		exit(1);
	}
	status = 1;
	waitpid(child, &status, 0);
//	if (waitpid(child, &status, 0) != child)
//		ft_dprintf(2, "Error during waiting child pid %d\n", child);
	g_child = 0;
	return (1);
}
