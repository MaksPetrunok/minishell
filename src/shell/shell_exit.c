/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 02:32:57 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/28 15:45:43 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

int	finish_child_processes(void)
{
	t_list		*lst;
	t_list		*tmp;
	t_process	*process;
	int			count;

	count = 0;
	lst = g_shell.childs;
	while (lst)
	{
		tmp = lst->next;
		process = (t_process *)(lst->content);
		kill(process->pid, SIGKILL);
		free(lst->content);
		free((void *)lst);
		lst = tmp;
		count++;
	}
	g_shell.childs = NULL;
	return (count);
}

int	add_child_process(pid_t pid)
{
	t_list		*elem;
	t_process	process;

	process.pid = pid;
	if ((elem = ft_lstnew((void *)(&process), sizeof(t_process))) == 0)
		return (-1);
	elem->next = g_shell.childs;
	g_shell.childs = elem;
	return (0);
}

void	free_history(void)
{
	t_dlist	*lst;
	t_dlist *tmp;

	lst = g_shell.history->stack;
	while (lst)
	{
		tmp = lst->next;
		free((void *)(lst->str));
		free((void *)lst);
		lst = tmp;
	}
	free((void *)(g_shell.history));
}
