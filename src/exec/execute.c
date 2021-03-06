/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:39:33 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 19:47:20 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*search_path(const char *name, char *path)
{
	char	**dirs_ref;
	char	**dirs;
	char	*ret;

	if ((ret = hmap_get(name, g_shell.binary)) != 0 && access(ret, F_OK) == 0)
		return (ft_strdup(ret));
	if ((dirs = ft_strsplit(path, ':')) == 0)
		return (0);
	dirs_ref = dirs;
	while (*dirs)
	{
		if ((ret = ft_strjoin3(*dirs, "/", name)) != 0)
		{
			if (access(ret, F_OK) == 0)
			{
				free((void *)dirs_ref);
				return (ret);
			}
			free((void *)ret);
		}
		dirs++;
	}
	free((void *)dirs_ref);
	return (0);
}

static char	*get_exec_path(const char *name)
{
	char	*ret;
	char	*path;
	char	cwd[4000];

	if (ft_strchr(name, '/') != 0)
	{
		getcwd(cwd, 4000);
		if (*name == '/')
			ret = ft_strdup(name);
		else
			ret = ft_strjoin3(cwd, "/", name);
		if (ret == NULL)
			return (0);
		if (access(ret, F_OK) == 0)
			return (ret);
		free((void *)ret);
		return (0);
	}
	path = get_var("PATH", g_shell.environ);
	if (!path || !(*path))
		return (0);
	ret = search_path(name, path);
	return (ret);
}

void		launch_process(char **av, t_env *env)
{
	char	*cmd;
	t_func	builtin;

	if ((builtin = get_builtin(*av)) != NULL)
	{
		builtin(av, env);
		return ;
	}
	cmd = get_exec_path(av[0]);
	if (cmd && *av && **av)
	{
		if (access(cmd, X_OK) == 0)
		{
			execve(cmd, av, env->av);
			ft_dprintf(2, "%s: %s: command not found\n",
													SHELL_NAME, *av);
		}
		else
			ft_dprintf(2, "%s: %s: access denied\n", SHELL_NAME, *av);
	}
	else
		ft_dprintf(2, "%s: %s: command not found\n", SHELL_NAME, *av);
}

int			execute(char **av, t_env *env)
{
	pid_t	child;
	int		status;

	if ((child = fork()) == 0)
	{
		launch_process(av, env);
		exit(127);
	}
	else if (child < 0)
	{
		ft_dprintf(2, "%s: failed to launch new process '%s'\n",
												SHELL_NAME, av[0]);
		return (-1);
	}
	else
	{
		add_child_process(child);
	}
	waitpid(child, &status, 0);
	g_shell.last_ret = WEXITSTATUS(status);
	finish_child_processes();
	return (1);
}

int			execute_redir(char **av, t_env *env, char **io)
{
	pid_t	child;
	int		status;

	if ((child = fork()) == 0)
	{
		redirect_io(io);
		launch_process(av, env);
		exit(127);
	}
	else if (child < 0)
	{
		ft_dprintf(2, "%s: failed to launch new process '%s'\n",
												SHELL_NAME, av[0]);
		return (-1);
	}
	else
	{
		add_child_process(child);
	}
	waitpid(child, &status, 0);
	g_shell.last_ret = WEXITSTATUS(status);
	finish_child_processes();
	return (1);
}
