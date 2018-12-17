/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 19:30:36 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/13 20:30:52 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*get_files(t_inp_buff *buff, DIR *dstr)
{
	struct dirent	*dirp;
	char			dir[4100];
	char			*patt;
	t_list			*lst;
	int				i;

	getcwd(dir, 4100);
	patt = convert_pattern(buff);
	if ((dstr = opendir(dir)) == 0)
		return (0);
	lst = 0;
	while ((dirp = readdir(dstr)) != 0)
		if (patt == 0)
			add_file(dirp->d_name, &lst);
		else
		{
			i = 0;
			while (patt[i] && dirp->d_name[i] == patt[i])
				i++;
			if (i > 0 && dirp->d_name[i] && patt[i] == '\0')
				add_file(dirp->d_name + i, &lst);
		}
	closedir(dstr);
	free((void *)patt);
	return (lst);
}

int				file_complete(t_inp_buff *buff)
{
	t_list	*match;
	t_list	*head;
	char	*str;
	DIR		*dstr;

	dstr = 0;
	match = get_files(buff, dstr);
	head = match;
	while (match && ft_lstsize(head) > 1)
	{
		techo("\n");
		techo((char *)(match->content));
		match = match->next;
	}
	if (ft_lstsize(head) > 1)
	{
		techo("\n");
		show_prompt();
		if (*(str = inp_to_str(buff->data)))
			techo(str);
		free((void *)str);
	}
	fill_input(buff, head);
	ft_lstfree(&head);
	return (1);
}
