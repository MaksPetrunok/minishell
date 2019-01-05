/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 19:13:03 by mpetruno          #+#    #+#             */
/*   Updated: 2019/01/05 20:23:37 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_cursor(int rows)
{
	int	diff;
	int	prompt_to_current;
	int	cmd_to_current;

	diff = g_shell.winsize.ws_row - 1 - g_shell.positions.current.row;
	if (rows > diff)
	{
		prompt_to_current = g_shell.positions.current.row -
							g_shell.positions.prompt.row;
		cmd_to_current = g_shell.positions.current.row -
						g_shell.positions.cmd.row;
		g_shell.positions.current.row = g_shell.winsize.ws_row - 1 - rows;
		g_shell.positions.prompt.row = g_shell.positions.current.row -
										prompt_to_current;
		g_shell.positions.cmd.row = g_shell.positions.current.row -
									cmd_to_current;
	}
	move_cursor(g_shell.positions.current.col, g_shell.positions.current.row);
}

static void	refresh_inp(void)
{
	int	i;

	i = 0;
	write(1, "\n", 1);
	show_prompt();
	while (g_shell.input->data[i])
		ft_putstr(g_shell.input->data[i++]);
	set_cursor(&(g_shell.positions.current));
	g_shell.positions.prompt.row = g_shell.winsize.ws_row - 1 -
		(g_shell.plen + g_shell.input->len) / g_shell.winsize.ws_col;
	g_shell.positions.cmd.row = g_shell.positions.prompt.row +
		g_shell.plen / g_shell.winsize.ws_col;
}

static void	print_table(char **names, int size, int max_len)
{
	int	cols;
	int	rows;
	int	i;
	int	j;

	cols = g_shell.winsize.ws_col / max_len;
	rows = size / cols + (size % cols > 0);
	i = 0;
	while (i < rows)
	{
		j = 0;
	write(1, "\n", 1);
		while (j < cols - 1 && i * cols + j < size - 1)
		{
			ft_printf("%-*s", max_len, names[i * cols + j]);
			j++;
		}
		ft_printf("%s", names[i * cols + j]);
		i++;
	}
	if (rows + 1 >= g_shell.winsize.ws_row)
		refresh_inp();
	else
		update_cursor(rows);
}

void		print_options(t_list *lst)
{
	char	**names;
	int		i;
	int		len;
	int		max_len;

	clear_from_cursor(g_shell.input);
	if ((names = malloc(sizeof(char **) * (ft_lstsize(lst) + 1))) == NULL)
		return ;
	i = 0;
	len = 0;
	max_len = 0;
	while (lst)
	{
		names[i] = (char *)(lst->content);
		len = ft_strlen(names[i]);
		if (len > max_len)
			max_len = len;
		lst = lst->next;
		i++;
	}
	names[i] = NULL;
	print_table(names, i, max_len + 1);
	free((void *)names);
}
