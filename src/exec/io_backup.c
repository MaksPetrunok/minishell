/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_backup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 18:17:38 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/28 18:18:08 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		backup_stdio(void)
{
	g_shell.io_backup[0] = dup(0);
	g_shell.io_backup[1] = dup(1);
	g_shell.io_backup[2] = dup(2);
	if (g_shell.io_backup[0] == -1 ||
		g_shell.io_backup[1] == -1 ||
		g_shell.io_backup[2] == -1)
	{
		ft_dprintf(2, "cannot backup stdio file descriptors\n");
		close(g_shell.io_backup[0]);
		close(g_shell.io_backup[1]);
		close(g_shell.io_backup[2]);
		g_shell.io_backup[0] = -1;
		g_shell.io_backup[1] = -1;
		g_shell.io_backup[2] = -1;
		return (0);
	}
	return (1);
}

void	restore_stdio(void)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (g_shell.io_backup[i] != -1)
		{
			dup2(g_shell.io_backup[i], i);
			close(g_shell.io_backup[i]);
			g_shell.io_backup[i] = -1;
		}
		i++;
	}
}
