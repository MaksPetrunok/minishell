/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:40:55 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/18 11:06:56 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(char __attribute__((unused)) **av,
				t_env __attribute__((unused)) *env)
{
	char	cwd[4100];

	getcwd(cwd, 4100);
	ft_printf("%s\n", cwd);
	g_shell.last_ret = 0;
	return (1);
}
