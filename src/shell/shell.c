/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 20:10:49 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/20 16:36:03 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_shlvl(void)
{
	char	*lvl_str;
	int		lvl;

	if ((lvl_str = get_var("SHLVL", g_shell.environ)) == NULL)
	{
		set_var("SHLVL", "1", g_shell.environ);
		return ;
	}
	lvl = ft_atoi(lvl_str);
	if (lvl < 0)
		lvl = 0;
	lvl++;
	if ((lvl_str = ft_itoa(lvl)) == NULL)
		return ;
	set_var("SHLVL", lvl_str, g_shell.environ);
	free((void *)lvl_str);
}

int			add_child_process(pid_t pid)
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

unsigned long	get_path_hash(void)
{
	char	*path;

	path = get_var("PATH", g_shell.environ);
	if (path == NULL)
		return (0);
	else
		return (hash(path));
}

static void	init_fields(void)
{
	g_shell.binary = NULL;
	g_shell.path_hash = 0;
	g_shell.childs = NULL;
	g_shell.input = NULL;
	g_shell.last_ret = 0;
	g_shell.is_fork = 0;
	g_shell.inp_state = S_GEN;
	g_shell.const_input = NULL;
	g_shell.io_backup[0] = -1;
	g_shell.io_backup[1] = -1;
	g_shell.io_backup[2] = -1;
}

int			init_shell(char **env)
{
	init_fields();
	if ((g_shell.environ = init_environment(env)) == NULL)
		return (-1);
	set_shlvl();
	if (ioctl(0, TIOCGWINSZ, &(g_shell.winsize)) == -1)
		return (-1);
	upd_binary_lst();
	if (setup_terminal() != 0 || init_history() != 0)
	{
		free_hashmap(g_shell.binary);
		env_free(g_shell.environ);
		return (-1);
	}
	init_cursor();
	setup_signals();
	g_shell.clipboard = NULL;
	return (0);
}
