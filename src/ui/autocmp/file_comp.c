/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 19:30:36 by mpetruno          #+#    #+#             */
/*   Updated: 2019/01/06 21:42:02 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		set_path_start(char **path, char *inp)
{
	int	i;

	i = 0;
	*path = inp;
	while (inp[i])
	{
		if (inp[i] == ' ' || inp[i] == '\t' || inp[i] == ';')
			*path = inp + i + 1;
		i++;
	}
}

static void		get_dir(t_inp_buff *buff, char *dir, size_t size)
{
	char	*inp;
	char	*path;
	char	*slash;
	int		len;

	inp = inp_to_str(buff->data);
	set_path_start(&path, inp);
	getcwd(dir, size);
	if ((slash = ft_strrchr(path, '/')) != NULL)
		*slash = '\0';
	if (path == slash)
		ft_strcpy(dir, "/");
	else if (*path == '/')
		ft_strcpy(dir, path);
	else if (slash && slash - path + ft_strlen(dir) < size - 1)
	{
		len = ft_strlen(dir);
		dir[len] = '/';
		ft_strcpy(dir + len + 1, path);
	}
	free((void *)inp);
}

static int		is_dir(char *name, char *dir)
{
	char		*path;
	struct stat	st;
	int			res;

	if ((path = ft_strjoin3(dir, "/", name)) == NULL)
		return (0);
	res = 0;
	if (stat(path, &st) == 0)
		if (S_ISDIR(st.st_mode))
			res = 1;
	free((void *)path);
	return (res);
}

static t_list	*get_files(t_inp_buff *buff, DIR *dstr)
{
	struct dirent	*dirp;
	char			dir[4100];
	char			*patt;
	t_list			*lst;
	int				i;

	get_dir(buff, dir, 4100);
	patt = convert_pattern(buff);
	if ((dstr = opendir(dir)) == 0)
		return (0);
	lst = 0;
	while ((dirp = readdir(dstr)) != 0)
		if ((patt == NULL || *patt == '\0') && *(dirp->d_name) != '.')
			add_file(dirp->d_name, &lst, is_dir(dirp->d_name, dir));
		else if (patt != NULL)
		{
			i = 0;
			while (patt[i] && dirp->d_name[i] == patt[i])
				i++;
			if (i > 0 && dirp->d_name[i] && patt[i] == '\0')
				add_file(dirp->d_name, &lst, is_dir(dirp->d_name, dir));
		}
	closedir(dstr);
	free((void *)patt);
	return (lst);
}

int				file_complete(t_inp_buff *buff)
{
	t_list	*match;
	t_list	*head;
	DIR		*dstr;

	dstr = 0;
	match = get_files(buff, dstr);
	head = match;
	refresh_ui(buff, head);
	if (ft_lstsize(head) > 1)
		print_options(head);
	ft_lstfree(&head);
	return (1);
}
