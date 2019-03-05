/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 11:55:26 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 18:54:07 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	open_var(t_token *tkn, char *name)
{
	char	*str;
	char	*join;

	if (*name == '?')
		str = ft_itoa(g_shell.last_ret);
	else if (*name == '$')
		str = ft_itoa((int)getpid());
	else
		str = get_var(name, g_shell.environ);
	if (str == NULL)
		return (0);
	if ((join = ft_strjoin(tkn->data, str)) == NULL)
	{
		ft_dprintf(2, "allocation error\n");
		return (-1);
	}
	free((void *)(tkn->data));
	tkn->data = join;
	tkn->pos = ft_strlen(join);
	tkn->size = tkn->pos;
	if (*name == '?' || *name == '$')
		free((void *)str);
	return (0);
}

int	expand_var(t_token *tkn, char **inp)
{
	char	*name;
	int		i;
	int		ret;

	name = NULL;
	if (**inp == '?' || **inp == '$')
		name = *inp;
	else
	{
		if ((name = ft_strnew(ft_strlen(*inp) + 1)) == NULL)
		{
			ft_dprintf(2, "allocation error\n");
			return (-1);
		}
		i = 0;
		while (ft_isalnum(**inp) || **inp == '_')
			name[i++] = *(*inp)++;
		*inp -= 1;
	}
	ret = open_var(tkn, name);
	if (name != *inp)
		free((void *)name);
	return (ret);
}

int	expand_str(t_token **tkn, char **inp)
{
	if (**inp == '~')
		return (expand_tilde(*tkn));
	else if (**inp == '$' && *(*inp + 1) == '\0')
	{
		tkn_add(tkn, inp);
		return (0);
	}
	else if (**inp == '$')
	{
		*inp += 1;
		return (expand_var(*tkn, inp));
	}
	ft_dprintf(2, "trying to expand something not equal $ or ~\n");
	return (-1);
}
