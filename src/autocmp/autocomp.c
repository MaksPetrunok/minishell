/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 19:30:36 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/18 13:56:33 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		sort(void *a, void *b)
{
	char	*aa;
	char	*bb;

	aa = (char *)a;
	bb = (char *)b;
	return (ft_strcmp(aa, bb));
}

void	add_file(char *file, t_list **lst)
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

char	*convert_pattern(t_inp_buff *buff)
{
	char	**start;
	char	*patt;
	int		i;

	if (buff->data[buff->len - 1][0] == ' ' ||
		buff->data[buff->len - 1][0] == '\t' || buff->len == 0)
		return (0);
	i = buff->len - 1;
	while (i >= 0 && buff->data[i][0] != ' ' && buff->data[i][0] != '\t')
		i--;
	start = buff->data + i + 1;
	patt = inp_to_str(start);
	return (patt);
}

void	fill_input(t_inp_buff *buff, t_list *head)
{
	t_list	*lst;
	int		i;
	int		add;
	char	*tmp;
	char	sym[2];

	i = 0;
	add = 1;
	sym[1] = '\0';
	while (head && add)
	{
		lst = head;
		add = 1;
		sym[0] = *(char *)((lst->content) + i);
		while (lst && add)
		{
			tmp = (char *)(lst->content);
			if (!tmp[i] || tmp[i] != sym[0])
				add = 0;
			lst = lst->next;
		}
		if (add)
			inp_insert(buff, sym);
		i++;
	}
}

int		auto_complete(t_inp_buff *buff)
{
	int	i;
	int	words;

	if (buff->pos != buff->len)
		return (1);
	i = 0;
	words = 0;
	while (i < buff->len - 1)
	{
		if (buff->data[i][0] != ' ' && buff->data[i][0] != '\t' &&
			(buff->data[i + 1][0] == ' ' || buff->data[i + 1][0] == '\t'))
			words++;
		if (buff->data[i][0] == ';')
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
