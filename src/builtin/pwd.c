/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:40:55 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/12 15:54:22 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

int	builtin_pwd(char __attribute__((unused)) **av)
{
	char	cwd[4100];

	getcwd(cwd, 4100);
	ft_printf("%s\n", cwd);
	g_shell.last_ret = 0;
	return (1);
}
