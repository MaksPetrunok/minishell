/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:34:43 by mpetruno          #+#    #+#             */
/*   Updated: 2019/01/06 17:56:29 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_execs(t_list **lst, char *dir, char *patt)
{
	DIR				*dstr;
	struct dirent	*dirp;
	struct stat		st;
	char			*pathname;

	if ((dstr = opendir(dir)) == NULL)
		return ;
	while ((dirp = readdir(dstr)) != NULL)
	{
		pathname = ft_strjoin3(dir, "/", dirp->d_name);
		stat(pathname, &st);
		if (S_ISREG(st.st_mode) && access(pathname, X_OK) == 0 &&
			ft_strstr(dirp->d_name, patt) == dirp->d_name)
		{
			add_file(dirp->d_name, lst, 0);
		}
		free((void *)pathname);
	}
	closedir(dstr);
}

void		get_bin_lst(t_inp_buff *buff, t_list **lst)
{
	char	**path_lst;
	char	*path;
	int		i;
	char	*patt;

	path = get_var("PATH", g_shell.environ);
	patt = convert_pattern(buff);
	if (path == NULL)
		return ;
	if ((path_lst = ft_strsplit(path, ':')) == NULL)
	{
		free((void *)patt);
		return ;
	}
	i = 0;
	while (path_lst[i])
	{
		add_execs(lst, path_lst[i++], patt);
	}
	arr_free((void **)path_lst);
	free((void *)patt);
}
