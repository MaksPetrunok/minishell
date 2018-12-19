/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 20:10:49 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/18 14:09:27 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

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

int			init_shell(char **env)
{
	g_shell.childs = NULL;
	g_shell.input = NULL;
	g_shell.last_ret = 0;
	if ((g_shell.environ = init_environment(env)) == 0)
		return (-1);
	set_shlvl();
	if (setup_terminal() != 0)
	{
		env_free(g_shell.environ);
		return (-1);
	}
	if (init_cursor() != 0)
	{
		exit_shell();
		return (-1);
	}
	if (ioctl(0, TIOCGWINSZ, &(g_shell.w)) == -1)
		return (-1);
	setup_signals();
	return (0);
}

void		exit_shell(void)
{
	finish_child_processes();
	if (switch_term_to(g_shell.term_default) == -1)
		ft_dprintf(2, "%s: unable restore terminal settings\n", SHELL_NAME);
	free_child_list();
	free_terminals();
	env_free(g_shell.environ);
	free((void *)(g_shell.cursor));
}
