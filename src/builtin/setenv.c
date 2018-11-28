/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:41:13 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/28 18:41:14 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_setenv(char **av)
{
	if (ft_arrsize((void **)av) > 3)
	{
		ft_putstr_fd("setenv: too many arguments\n", 2);
		return (1);
	}
	if (av[1] == 0)
		return (builtin_env(av));
	set_var(av[1], av[2]);
	return (1);
}
