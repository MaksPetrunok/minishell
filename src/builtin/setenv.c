/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:41:13 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/10 06:39:52 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_setenv(char **av)
{
	int		size;
	char	*ptr;

	if (av[1] == 0)
		return (builtin_env(av));
	size = ft_arrsize((void **)av);
	if ((ptr = ft_strchr(av[1], '=')) != NULL)
	{
		*ptr = '\0';
		if (size > 2)
			ft_putstr_fd("setenv: too many arguments\n", 2);
		else
			set_var(av[1], ptr + 1);
	}
	else if (size > 3)
		ft_putstr_fd("setenv: too many arguments\n", 2);
	else
		set_var(av[1], av[2]);
	return (1);
}
