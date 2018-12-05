/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 19:30:36 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/05 11:39:58 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		sort(void *a, void *b)
{
	char	*aa;
	char	*bb;

	aa = (char *)a;
	bb = (char *)b;
	return (ft_strcmp(aa, bb));
}

static void		add_file(const char *file, t_list **lst)
{
	t_list	*new;
	char	*data;

	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	data = ft_strdup(file);
	if (!data)
	{
		free((void *)new);
		return ;
	}
	new->content = (void *)data;
	ft_lstins(lst, new, sort);
}

char	*convert_pattern(long *data)
{
	long	*start;
	int		size;
	char	*patt;

	start = data;
	while (*data)
	{
		if (*data == (long)' ')
			start = data;
		data++;
	}
	size = data - start;
	patt = utf_to_str(start, size);
	return (patt);
}

static t_list	*get_files(long *data)
{
	DIR				*dstr;
	struct dirent	*dirp;
	char			dir[4100];
	char			*patt;
	t_list			*lst;

	getcwd(dir, 4100);
	patt = convert_pattern(data);
	if ((dstr = opendir(dir)) == 0)
		return (0);
	lst = 0;
	while ((dirp = readdir(dstr)) != 0)
		if (patt == 0 || ft_strstr(dirp->d_name, patt) == dirp->d_name)
		add_file(dirp->d_name, &lst);
	closedir(dstr);
	free((void *)patt);
	return (lst);
}



void	auto_complete(t_inp_buff *buff)
{
	t_list	*match;
	t_list	*head;

	match = get_files(buff->data);
	head = match;
//	if (ft_lstsize(match) == 1)
//	{	
//	}
	techo("\n");
	while (match)
	{
		techo((char *)(match->content));
		techo("\n");
		match = match->next;
	}
	ft_lstfree(&head);
//	system("leaks -fullContent minishell");
}

