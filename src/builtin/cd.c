/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:40:21 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/18 11:06:15 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(char *arg)
{
	char	*path;

	path = NULL;
	if (!arg || ft_strcmp(arg, "--") == 0)
		path = get_var("HOME", g_shell.environ);
	else if (ft_strcmp(arg, "-") == 0)
		path = get_var("OLDPWD", g_shell.environ);
	else if (access(arg, F_OK) == 0)
		path = arg;
	return (path);
}

static int	is_dir(char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
		return (0);
	return (S_ISDIR(st.st_mode));
}

static int	try_cd(char *dir)
{
	char	*path;

	if ((path = get_path(dir)) == 0)
	{
		if (dir == NULL || ft_strequ(dir, "--") || ft_strequ(dir, "~"))
			ft_putstr_fd("cd: HOME not set\n", 2);
		else if (ft_strequ(dir, "-"))
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
		else
			ft_dprintf(2, "cd: no such directory: %s\n", dir);
	}
	else if (!is_dir(path))
	{
		ft_dprintf(2, "cd: %s: not a directory\n", path);
	}
	else if (chdir(path) != 0)
	{
		if (access(path, F_OK))
			ft_dprintf(2, "cd: cannot open: %s\n", path);
		else
			ft_dprintf(2, "cd: access denied: %s\n", path);
	}
	else
		return (1);
	return (0);
}

int			builtin_cd(char **av)
{
	char	cwd[4100];
	char	new_dir[4100];

	getcwd(cwd, 4100);
	if (ft_arrsize((void **)av) > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		g_shell.last_ret = 1;
		return (1);
	}
	if (try_cd(av[1]))
	{
		set_var("OLDPWD", cwd, g_shell.environ);
		g_shell.last_ret = 0;
	}
	else
		g_shell.last_ret = 1;
	getcwd(new_dir, 4100);
	set_var("PWD", new_dir, g_shell.environ);
	return (1);
}
