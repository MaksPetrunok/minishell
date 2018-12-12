/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:41:13 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/12 18:19:04 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

int	builtin_setenv(char **av)
{
	int		size;
	char	*ptr;
	int		err;

	if (av[1] == 0)
		return (builtin_env(av));
	err = 0;
	size = ft_arrsize((void **)av);
	if ((ptr = ft_strchr(av[1], '=')) != NULL)
	{
		*ptr = '\0';
		if (size > 2)
			err = ft_dprintf(2, "setenv: too many arguments\n");
		else
			set_var(av[1], ptr + 1);
	}
	else if (size > 3)
		err = ft_dprintf(2, "setenv: too many arguments\n");
	else
		set_var(av[1], av[2]);
	g_shell.last_ret = err ? 1 : 0;
	return (1);
}
