/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:41:13 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/18 11:07:05 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wrong_name_msg(char *expr)
{
	char	*ptr;

	if ((ptr = ft_strchr(expr, '=')) != NULL)
		*ptr = '\0';
	return (ft_dprintf(2, "setenv: not and identifier: %s\n", expr));
}

int			builtin_setenv(char **av, t_env *env)
{
	int		size;
	char	*ptr;
	int		err;

	if (av[1] == 0)
		return (builtin_env(av, env));
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
			set_var(av[1], ptr + 1, env);
	}
	else if (size > 3)
		err = ft_dprintf(2, "setenv: too many arguments\n");
	else
		set_var(av[1], av[2], env);
	g_shell.last_ret = err ? 1 : 0;
	return (1);
}
