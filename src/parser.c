/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 19:19:19 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/05 15:13:50 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	vector_size(t_token *tkn)
{
	int	size;

	size = 0;
	while (tkn)
	{
		if (tkn->type == CH_SEMICOLON)
			return (size);
		size++;
		tkn = tkn->next;
	}
	return (size);
}

static char	*get_value(t_token *tkn)
{
	char	*tmp;
	char	*ret;

	if (tkn->type == CH_GENERAL)
		tmp = tkn->data;
	else if (tkn->data[0] == '~')
	{
		if (tkn->data[1] == '\0')
			tmp = get_var("HOME");
		else
			tmp = ft_strdup(tkn->data);
	}
	else
		tmp = get_var(tkn->data + 1);
	if (tmp == 0)
		ret = ft_strnew(0);
	else
		ret = ft_strdup(tmp);
	return (ret);
}

static char	*join(char *s1, char *s2)
{
	char	*tmp;

	if (s1 == 0 && s2 == 0)
		return (0);
	else if (s1 == 0)
		tmp = ft_strdup(s2);
	else if (s2 == 0)
		tmp = ft_strdup(s1);
	else
		tmp = ft_strjoin(s1, s2);
	free((void *)s1);
	free((void *)s2);
	return (tmp);
}

char	**parse_cmd(t_token **tkn)
{
	char	**av;
	char	*buff;
	char	**ref;
	int		size;
	int		increment;

	size = vector_size(*tkn);
	if (size == 0 || (av = ft_memalloc(sizeof(char **) * (size + 1))) == 0)
		return (0);
	ref = av;
	while (*tkn && size-- > 0)
	{

		increment = (*tkn)->complete;

		//move to separate function set_argument()
		buff = get_value(*tkn);
		if (!buff && !(*av))
			return (0);
		if ((*tkn)->complete)
		{
			*av = join(*av, buff);
			av++;
		}
		else
			*av = join(*av, buff);
		//end move
		*tkn = (*tkn)->next;
	}
	av = increment ? av : av + 1;
	*av = 0;
	return (ref);
}
