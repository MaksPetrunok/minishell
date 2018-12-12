/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:39:33 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/12 21:50:00 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

static char	**tokenize_split(char *s, char *delim)
{
	char	**tokens;
	int		i;
	int		state;

	tokens = malloc(sizeof(char **) * 16);
	i = 0;
	state = 0;
	while (*s && i < 15)
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
	ret = search_path(name, path);
	return (ret);
}

static void	launch_process(char **av)
{
	char	*cmd;

	cmd = get_exec_path(av[0]);
	if (cmd && *av && **av)
	{
		if (access(cmd, X_OK) == 0)
		{
			
			ft_printf("exec path = %s\n", cmd);
			for (int i=0; av[i] != 0; i++)
				ft_printf("av[%d]=%s\n", i, av[i]);
//			for (int i=0; g_shell.environ->av[i] != 0; i++)
//				ft_printf("env[%d]=%s\n", i, g_shell.environ->av[i]);
			ft_printf("----------------------\n");
				
			execve(cmd, av, g_shell.environ->av);
			ft_dprintf(2, "%s: %s: Failed to launch the command\n",
													SHELL_NAME, av[0]);
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

	if ((child = fork()) == 0)
	{
		switch_term_to(g_shell.term_default);
		launch_process(av);
		exit(127);
	}
	else if (child < 0)
	{
		ft_dprintf(2, "%s: failed to launch new process '%s'\n",
												SHELL_NAME, av[0]);
		return (-1);
	}
	else
		add_child_process(child);
	status = 1;
	waitpid(child, &status, 0);
	g_shell.last_ret = WEXITSTATUS(status);
	finish_child_processes();
	switch_term_to(g_shell.term_typing);
	return (1);
}
