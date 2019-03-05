/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 15:41:06 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 16:33:50 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_input(char *path)
{
	int	fd;

	if ((fd = open(path, O_RDONLY)) == -1)
	{
		free((void *)path);
		ft_dprintf(2, "%s: %s: permission denied\n", SHELL_NAME, path);
		return (0);
	}
	if (dup2(fd, 0) == -1)
	{
		ft_dprintf(2, "%s: %s: error occured\n", SHELL_NAME, path);
		return (0);
	}
	close(fd);
	free((void *)path);
	return (1);
}

int	init_input(int ac, char **av)
{
	char	*path;
	char	cwd[4100];

	if (ac > 2)
	{
		ft_dprintf(2, "%s: too many arguments\n", SHELL_NAME);
		return (0);
	}
	if (ac < 2)
	{
		g_shell.interactive = 1;
		return (1);
	}
	g_shell.interactive = 0;
	getcwd(cwd, 4100);
	if (av[1][0] == '/')
		path = ft_strdup(av[1]);
	else
		path = ft_strjoin3(cwd, "/", av[1]);
	if (path == NULL || access(path, F_OK))
	{
		ft_dprintf(2, "%s: file '%s' not found\n", SHELL_NAME, path);
		free((void *)path);
		return (0);
	}
	if (!set_input(path))
		return (0);
	return (1);
}
