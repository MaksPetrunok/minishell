/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 02:32:57 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/10 02:32:58 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	finish_child_processes(void)
{
	t_list		*lst;
	t_process	*process;

	lst = shell.childs;
	while (lst)
	{
		process = (t_process *)(lst->content);
		kill(process->pid, SIGKILL);
		lst = lst->next;
	}
}
