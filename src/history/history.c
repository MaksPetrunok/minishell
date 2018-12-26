// header

#include "minishell.h"

t_shell	g_shell;

int	inp_hist_prev(t_inp_buff *buff, char *sym)
{
	(void)buff;
	(void)sym;
	t_dlist	*lst;

	lst = g_shell.history->stack;
	while (lst)
	{
		ft_printf("%s\n", lst->str);
		lst = lst->next;
	}
	return (1);
}

int	inp_hist_next(t_inp_buff *buff, char *sym)
{
	(void)buff;
	(void)sym;
	ft_printf("history next");
	return (1);
}

int	history_add(char *cmd)
{
	t_dlist	*item;

	if ((item = malloc(sizeof(t_dlist))) == NULL)
		return (0);
	if ((item->str = ft_strdup(cmd)) == NULL)
	{
		free((void *)item);
		return (0);
	}
	item->prev = NULL;
	item->next = g_shell.history->stack;
	g_shell.history->stack = item;
	g_shell.history->iter = item;
	return (1);
}

int	init_history(void)
{
	if ((g_shell.history = malloc(sizeof(t_history))) == NULL)
		return (-1);
	g_shell.history->stack = NULL;
	g_shell.history->iter = NULL;
	return (0);
}
