/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:41:13 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/18 14:04:28 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

static int	wrong_name_msg(char *expr)
{
	char	*ptr;

	if ((ptr = ft_strchr(expr, '=')) != NULL)
		*ptr = '\0';
	return (ft_dprintf(2, "setenv: not and identifier: %s\n", expr));
}

int			builtin_setenv(char **av)
{
	int		size;
	char	*ptr;
	int		err;

	if (av[1] == 0)
		return (builtin_env(av));
	err = 0;
	size = ft_arrsize((void **)av);
	if (!ft_isalpha(av[1][0]) && av[1][0] != '_')
		err = wrong_name_msg(av[1]);
	else if ((ptr = ft_strchr(av[1], '=')) != NULL)
	{
		*ptr = '\0';
		if (size > 2)
			err = ft_dprintf(2, "setenv: too many arguments\n");
		else
			set_var(av[1], ptr + 1, g_shell.environ);
	}
	else if (size > 3)
		err = ft_dprintf(2, "setenv: too many arguments\n");
	else
		set_var(av[1], av[2], g_shell.environ);
	g_shell.last_ret = err ? 1 : 0;
	return (1);
}
