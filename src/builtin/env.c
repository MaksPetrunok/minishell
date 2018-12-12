/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:40:36 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/12 15:55:31 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

int	builtin_env(char __attribute__((unused)) **av)
{
	char	**e;
	int		i;

	i = 0;
	e = g_shell.environ->av;
	while (e[i])
		ft_printf("%s\n", e[i++]);
	g_shell.last_ret = 0;
	return (1);
}
