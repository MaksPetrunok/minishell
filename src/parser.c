/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 19:19:19 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/30 22:49:54 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * SYNTAX for TOKEN LIST:
 *
 * token : data = (string with data)\0
 * 		 : add_next = 0 | 1
 * 		 : type = CH_GENERAL | CH_EXPR | CH_SEMICOLON
 * 		 : next = token | NULL
 *
 * ptree : int	type
 * 		 : char **av
 * 		 : ptree left
 * 		 : ptree right
 *
 *
 * Note: if add_next = 0 and next->type = CH_GENERAL | CH_EXPR then
 * append next->data to ->data. If add_next = 1 then add next->data
 * as next value in vector
 */

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

	if (tkn->type == CH_GENERAL)
		return (ft_strdup(tkn->data));
	if (tkn->data[0] == '~')
	{
		if (tkn->data[1] == '\0')
			tmp = get_var("HOME");
		else
			return (ft_strdup(tkn->data));
	}
	else
		tmp = get_var(tkn->data + 1);
	if (tmp == 0)
		tmp = ft_strnew(0);
	return (tmp);
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
	int		size;
	char	**ref;

	size = vector_size(*tkn);
	if (size == 0 || (av = ft_memalloc(sizeof(char **) * (size + 1))) == 0)
		return (0);
	ref = av;
	while (*tkn && size-- > 0)
	{
		buff = get_value(*tkn);
		if ((*tkn)->complete)
		{
			*av = join(*av, buff);
			av++;
		}
		else
			*av = join(*av, buff);
		*tkn = (*tkn)->next;
	}
	return (ref);
}
