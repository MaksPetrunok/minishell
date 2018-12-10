/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:40:21 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/10 06:11:17 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(char *arg)
{
	char	*path;

	path = 0;
	if (!arg || ft_strcmp(arg, "--") == 0)
		path = get_var("HOME");
	else if (ft_strcmp(arg, "-") == 0)
		path = get_var("OLDPWD");
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
		ft_dprintf(2, "cd: no such directory: %s\n", dir);
		return (0);
	}
	else if (!is_dir(path))
	{
		ft_dprintf(2, "cd: %s: not a directory\n", path);
		return (0);
	}
	else if (chdir(path) != 0)
	{
		ft_dprintf(2, "cd: cannot open '%s'\n", path);
		return (0);
	}
	return (1);
}

int			builtin_cd(char **av)
{
	char	cwd[4100];
	char	new_dir[4100];

	getcwd(cwd, 4100);
	if (ft_arrsize((void **)av) > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	if (try_cd(av[1]))
	{
		getcwd(new_dir, 4100);
		set_var("OLDPWD", cwd);
		set_var("PWD", new_dir);
	}
	return (1);
}
