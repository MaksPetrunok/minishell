/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 20:10:49 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/20 16:36:03 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_binary(char *dir)
{
	DIR				*dstr;
	struct dirent	*dirp;
	char			*path;

	if ((dstr = opendir(dir)) == NULL)
		return ;
	while ((dirp = readdir(dstr)) != NULL)
	{
		if (*(dirp->d_name) == '.')
			continue ;
		if ((path = ft_strjoin3(dir, "/", dirp->d_name)) == NULL)
			continue ;
		hmap_set(dirp->d_name, path, g_shell.binary);
		free((void *)path);
	}
	closedir(dstr);
	free((void *)dir);
}

void	upd_binary_lst(void)
{
	char	*path;
	char	**dirs;
	int		i;

	if ((path = get_var("PATH", g_shell.environ)) == NULL)
		return ;
	if (g_shell.path_hash == hash(path))
		return ;
	g_shell.path_hash = hash(path);
	if (*path == '\0')
		return ;
	if ((dirs = ft_strsplit(path, ':')) == NULL)
		return ;
	free_hashmap(g_shell.binary);
	if ((g_shell.binary = init_hashmap(BINARY_HASHMAP_SIZE)) == NULL)
	{
		ft_dprintf(2, "cannot create binary hashtable, allocation error\n");
		return ;
	}
	i = 0;
ft_printf("Updating binary table\n"); // debug
	while (dirs[i])
		fill_binary(dirs[i++]);
	free((void *)dirs);
}
