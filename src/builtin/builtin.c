/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:40:12 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/13 19:48:42 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin.h"

char		**get_builtin_list(char **list)
{
	short	i;

	i = 0;
	list[i++] = "exit";
	list[i++] = "pwd";
	list[i++] = "cd";
	list[i++] = "env";
	list[i++] = "setenv";
	list[i++] = "unsetenv";
	list[i++] = "echo";
	list[i] = 0;
	return (list);
}

static void	set_builtin_funcs(t_func *list)
{
	short	i;

	i = 0;
	list[i++] = &builtin_exit;
	list[i++] = &builtin_pwd;
	list[i++] = &builtin_cd;
	list[i++] = &builtin_env;
	list[i++] = &builtin_setenv;
	list[i++] = &builtin_unsetenv;
	list[i++] = &builtin_echo;
}

static int	get_builtin_index(const char *s)
{
	int		i;
	char	*names[10];

	get_builtin_list(names);
	i = 0;
	while (names[i])
	{
		if (ft_strcmp(s, names[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

t_func		get_builtin(const char *name)
{
	int			index;
	t_func		list[10];

	if (name == 0)
		return (0);
	set_builtin_funcs(list);
	index = get_builtin_index(name);
	if (index == -1)
		return (0);
	return (list[index]);
}
