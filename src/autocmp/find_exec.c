/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:34:43 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/18 13:57:05 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_execs(t_list **lst, char *dir, char *patt)
{
	DIR				*dstr;
	struct dirent	*dirp;
	struct stat		st;
	char			*pathname;
	t_list			*new;

	if ((dstr = opendir(dir)) == NULL)
		return ;
	while ((dirp = readdir(dstr)) != NULL)
	{
		pathname = ft_strjoin3(dir, "/", dirp->d_name);
		stat(pathname, &st);
		if (S_ISREG(st.st_mode) && access(pathname, X_OK) == 0 &&
			ft_strstr(dirp->d_name, patt) == dirp->d_name)
		{
			new = ft_lstnew((void *)(dirp->d_name), ft_strlen(dirp->d_name) + 1);
			ft_lstins(lst, new, &sort);
//			new->next = *lst;
//			*lst = new;
		}
		free((void *)pathname);
	}
	closedir(dstr);
}

t_list	*get_bin_lst(t_inp_buff *buff)
{
	t_list	*lst;
	char	**path_lst;
	char	*path;
	int		i;
	char	*patt;

	lst = NULL;
	path = get_var("PATH", g_shell.environ);
	patt = convert_pattern(buff);
	if (path == NULL)
		return (NULL);
	path_lst = ft_strsplit(path, ':');
	i = 0;
	while (path_lst[i])
		add_execs(&lst, path_lst[i++], patt);
	arr_free((void **)path_lst);
	free((void *)patt);
	return (lst);
}
