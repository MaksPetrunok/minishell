/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 19:13:03 by mpetruno          #+#    #+#             */
/*   Updated: 2019/01/04 21:10:24 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_table(char **names, int size, int max_len)
{
	int	cols;
	int	rows;
	int	i;
	int	j;

	cols = g_shell.winsize.ws_col / max_len;
	rows = size / cols + (size % cols > 0);
	i = 0;
	write(1, "\n", 1);
	while (i < rows)
	{
		j = 0;
		while (j < cols - 1 && i * cols + j < size - 1)
		{
			ft_printf("%-*s", max_len, names[i * cols + j]);
			j++;
		}
		ft_printf("%s\n", names[i * cols + j]);
		i++;
	}
}

void	print_options(t_list *lst)
{
	char	**names;
	int		i;
	int		len;
	int		max_len;

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
