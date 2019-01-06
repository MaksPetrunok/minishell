/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 19:30:36 by mpetruno          #+#    #+#             */
/*   Updated: 2019/01/06 21:05:08 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			sort(void *a, void *b)
{
	char	*aa;
	char	*bb;

	aa = (char *)a;
	bb = (char *)b;
	return (ft_strcmp(aa, bb));
}

void		add_file(char *file, t_list **lst, int is_dir)
{
	t_list	*new;
	char	*data;
	size_t	len;

	if ((new = malloc(sizeof(t_list))) == NULL)
		return ;
	len = ft_strlen(file);
	if ((data = malloc(len + 2)) == NULL)
	{
		free((void *)new);
		return ;
	}
	ft_strcpy(data, file);
	data[len++] = (is_dir) ? '/' : ' ';
	data[len] = '\0';
	new->content = (void *)data;
	new->content_size = ft_strlen(data);
	if (ft_lstinsuniq(lst, new, sort) == 0)
	{
		free((void *)data);
		free((void *)new);
	}
}

char		*convert_pattern(t_inp_buff *buff)
{
	char	**start;
	char	*patt;
	int		i;

	if (buff->len > 0 &&
		(buff->data[buff->len - 1][0] == ' ' ||
		buff->data[buff->len - 1][0] == '\t'))
		return (0);
	i = buff->len - 1;
	while (i >= 0 && buff->data[i][0] != ' ' && buff->data[i][0] != '\t' &&
			buff->data[i][0] != '/')
		i--;
	start = buff->data + i + 1;
	patt = inp_to_str(start);
	return (patt);
}

static int	is_relative_path(t_inp_buff *buff)
{
	char	*inp;
	char	*ptr;
	int		res;

	if ((inp = inp_to_str(buff->data)) == NULL)
		return (0);
	ptr = inp;
	while (*ptr && (*ptr == ' ' || *ptr == '\t'))
		ptr++;
	if (*ptr &&
		(*ptr == '/' ||
		ft_strstr(ptr, "./") == ptr ||
		ft_strstr(ptr, "../") == ptr))
	{
		res = 1;
	}
	else
		res = 0;
	free((void *)inp);
	return (res);
}

int			auto_complete(t_inp_buff *buff)
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
	if (words > 0 || is_relative_path(buff))
		file_complete(buff);
	else
		exec_complete(buff);
	return (1);
}
