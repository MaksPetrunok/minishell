/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 11:52:22 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/06 22:40:04 by mpetruno         ###   ########.fr       */
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

int	restore_term_ref(void)
{
	tconf("ei");
	if (tcsetattr(0, 0, shell.term_ref) != 0)
		return (-1);
	return (0);
}
