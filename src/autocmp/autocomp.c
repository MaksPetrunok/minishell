/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 19:30:36 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/13 21:31:25 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			add_file(char *file, t_list **lst)
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

char			*convert_pattern(t_inp_buff *buff)
{
	long	*start;
	char	*patt;
	int		i;

	if (buff->data[buff->len - 1] == (long)' ' ||
		buff->data[buff->len - 1] == (long)'\t' || buff->len == 0)
		return (0);
	i = buff->len - 1;
	while (buff->data[i] != (long)' ' && buff->data[i] != (long)'\t' &&
																i >= 0)
		i--;
	start = buff->data + i + 1;
	patt = utf_to_str(start, buff->len - i);
	return (patt);
}

void			fill(t_inp_buff **buff, t_list *head)
{
	t_list	*lst;
	int		i;
	int		add;
	char	*tmp;
	char	sym;

	i = 0;
	add = 1;
	while (head && add)
	{
		lst = head;
		add = 1;
		sym = *(char *)((lst->content) + i);
		while (lst && add)
		{
			tmp = (char *)(lst->content);
			if (!tmp[i] || tmp[i] != sym)
				add = 0;
			lst = lst->next;
		}
		if (add)
			inp_insert(buff, (int)sym);
		i++;
	}
	return ;
}

int				auto_complete(t_inp_buff **buff)
{
	int	i;
	int	words;

	if ((*buff)->pos != (*buff)->len)
		return (1);
	i = 0;
	words = 0;
	while (i < (*buff)->len)
	{
		if ((*buff)->data[i] != ' ' && (*buff)->data[i] != '\t' &&
			((*buff)->data[i + 1] == ' ' || (*buff)->data[i + 1] == '\t'))
			words++;
		if ((*buff)->data[i] == ';')
			words = 0;
		i++;
	}
	if (words > 0)
	{
		file_complete(buff);
	}
	else
	{
		exec_complete(buff);
	}
	return (1);
}
