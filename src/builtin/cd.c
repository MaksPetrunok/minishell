/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:40:21 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/28 18:45:33 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(char *arg)
{
	char	*path;

	if (!arg || ft_strcmp(arg, "--") == 0)
		path = get_var("HOME");
	else if (ft_strcmp(arg, "-") == 0)
		path = get_var("OLDPWD");
	else
		path = ft_strdup(arg);
	return (path);
}

static int	is_dir(char *path)
{
	struct stat	st;

	if (path == 0)
		return (0);
	if (stat(path, &st) != 0)
		return (0);
	return (S_ISDIR(st.st_mode));
}

static void	try_cd(char *dir, const char *cwd)
{
	char	*path;

	if ((path = get_path(dir)) == 0)
	{
		report_error(ERR_MALLOC);
		return ;
	}
	if (!is_dir(path))
	{
		ft_dprintf(2, "cd: %s: not a directory\n", path);
		free((void *)path);
		return ;
	}
	if (chdir(path) != 0)
	{
		ft_dprintf(2, "cd: cannot open '%s'\n", path);
		free((void *)path);
		return ;
	}
	set_var("OLDPWD", cwd);
	set_var("PWD", path);
	free((void *)path);
}

int			builtin_cd(char **av)
{
	char	cwd[4100];

	getcwd(cwd, 4100);
	if (ft_arrsize((void **)av) > 2)
		ft_putstr_fd("cd: too many arguments\n", 2);
	else
		try_cd(av[1], cwd);
	return (1);
}
