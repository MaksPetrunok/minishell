/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:40:36 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/11 22:44:27 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(char __attribute__((unused)) **av)
{
	char	**e;
	int		i;

	i = 0;
	e = shell.environ->av;
	while (e[i])
		ft_printf("%s\n", e[i++]);
	return (1);
}
