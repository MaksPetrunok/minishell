/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 11:55:26 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/15 16:19:41 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

int	expand_tilde(t_token *tkn)
{
	char	*home;
	char	*tmp;
	int		len;

	if ((home = get_var("HOME", g_shell.environ)) == NULL)
		return (-1);
	if ((tmp = ft_strjoin(tkn->data, home)) == NULL)
	{
		ft_dprintf(2, "allocation error\n");
		return (-1);
	}
	len = ft_strlen(tmp);
	tkn->pos = len;
	tkn->size = len;
	free((void *)(tkn->data));
	tkn->data = tmp;
	return (0);
}

int	expand_ss_to(char delim, t_token *tkn, char **inp)
{
	(void)delim;
	(void)tkn;
	(void)inp;
	return (0);
}

int	expand_var(t_token *tkn, char **inp)
{
	(void)tkn;
	(void)inp;
	return (0);
}

int	expand_str(t_token **tkn, char **inp)
{

	if (**inp == '~')
		return (expand_tilde(*tkn));
	else if (**inp == '`')
	{
		*inp += 1;
		return (expand_ss_to('`', *tkn, inp));
	}
	else if (**inp == '$' && *(*inp + 1) == '(')
	{
		*inp += 2;
		return (expand_ss_to(')', *tkn, inp));
	}
	else if (**inp == '$')
	{
		*inp += 1;
		return (expand_var(*tkn, inp));
	}
	ft_dprintf(2, "trying to expand something not equal $ or ~\n");
	return (-1);
}
