// header


#include "minishell.h"

pid_t	g_child;

void	sh_sig_handler(int __attribute__((unused))sig)
{
	if (g_child)
	{
		kill(g_child, SIGINT);
		g_child = 0;
		write(1, "\n", 1);
	}
	else
	{
		write(1, "\n", 1);
		show_prompt();
	}
}
