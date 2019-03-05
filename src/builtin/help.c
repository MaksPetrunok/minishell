/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 17:00:30 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 20:25:29 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_help(char **av, t_env *env)
{
	(void)env;
	if (av[1] == NULL)
		ft_printf("%s\n", HELP);
	else if (ft_strequ(av[1], "cd"))
		ft_printf("%s\n", US_CD);
	else if (ft_strequ(av[1], "echo"))
		ft_printf("%s\n", US_ECHO);
	else if (ft_strequ(av[1], "setenv"))
		ft_printf("%s\n", US_SETENV);
	else if (ft_strequ(av[1], "unsetenv"))
		ft_printf("%s\n", US_UNSETENV);
	else if (ft_strequ(av[1], "env"))
		ft_printf("%s\n", US_ENV);
	else if (ft_strequ(av[1], "exit"))
		ft_printf("%s\n", US_EXIT);
	else if (ft_strequ(av[1], "ui"))
		ft_printf("%s\n", US_UI);
	else
		ft_dprintf(2, "help: no entry found\n");
	return (1);
}
