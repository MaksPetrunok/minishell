//header

#include "minishell.h"

t_shell	shell;

static void	free_terminals()
{
	free((void *)(shell.term_ref));
	free((void *)(shell.term_current));
}

static void	free_child_list(void)
{
	t_list	*tmp;

	while (shell.childs)
	{
		tmp = shell.childs->next;
		free((void *)shell.childs->content);
		free((void *)shell.childs);
		shell.childs = tmp;
	}
}

int	init_shell(char **env)
{
	if ((shell.environ = init_environment(env)) == 0)
		return (-1);
	if (read_term_ref() == -1)
		return (-1);
	if (configure_term() == -1 ||
		init_cursor() == -1)
	{
		free_terminals();
		return (-1);
	}
	shell.childs = NULL;
	return (0);
}

void	exit_shell(void)
{
	finish_child_processes();
	if (restore_term_ref() == -1)
		ft_dprintf(2, "%s: unable restore terminal settings\n", SHELL_NAME);
	free_child_list();
	free_terminals();
	env_free(shell.environ);
	free((void *)(shell.cursor));
}
