/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 19:30:36 by mpetruno          #+#    #+#             */
/*   Updated: 2019/01/04 16:58:34 by mpetruno         ###   ########.fr       */
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
	new->content_size = ft_strlen(data);
	if (ft_lstinsuniq(lst, new, sort) == 0)
	{
		free((void *)data);
		free((void *)new);
	}
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
	while (i >= 0 && buff->data[i][0] != ' ' && buff->data[i][0] != '\t' &&
			buff->data[i][0] != '/')
		i--;
	start = buff->data + i + 1;
	patt = inp_to_str(start);
	return (patt);
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
