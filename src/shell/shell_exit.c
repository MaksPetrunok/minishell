/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 02:32:57 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 16:35:06 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_child_list(void)
{
	t_list	*tmp;

	while (g_shell.childs)
	{
		tmp = g_shell.childs->next;
		free((void *)g_shell.childs->content);
		free((void *)g_shell.childs);
		g_shell.childs = tmp;
	}
}

int			finish_child_processes(void)
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

void		free_history(void)
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

void		exit_shell(void)
{
	finish_child_processes();
	if (g_shell.interactive && switch_term_to(g_shell.term_default) == -1)
		ft_dprintf(2, "%s: unable restore terminal settings\n", SHELL_NAME);
	free_child_list();
	env_free(g_shell.environ);
	free_hashmap(g_shell.binary);
	free((void *)(g_shell.clipboard));
	if (!g_shell.interactive)
		return ;
	free_history();
	free_terminals();
}
