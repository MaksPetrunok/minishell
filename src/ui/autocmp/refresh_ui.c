/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 19:30:36 by mpetruno          #+#    #+#             */
/*   Updated: 2019/01/06 21:47:22 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_input(t_inp_buff *buff, t_list *head)
{
	t_list	*lst;
	int		i;
	int		add;
	char	*tmp;
	char	sym[2];

	i = 0;
	add = 1;
	sym[1] = '\0';
	while (head && add)
	{
		lst = head;
		add = 1;
		sym[0] = *(char *)((lst->content) + i);
		while (lst && add)
		{
			tmp = (char *)(lst->content);
			if (!tmp[i] || tmp[i] != sym[0])
				add = 0;
			lst = lst->next;
		}
		if (add)
			inp_insert(buff, sym);
		i++;
	}
}

void		refresh_ui(t_inp_buff *buff, t_list *lst)
{
	int	i;

	if (lst == NULL)
		return ;
	while (buff->pos > 0 && buff->data[buff->pos - 1][0] != ';')
	{
		i = buff->pos;
		if (buff->data[i - 1][0] == ' ' || buff->data[i - 1][0] == '\t' ||
			buff->data[i - 1][0] == '/')
			break ;
		inp_backsp(buff, 0);
	}
	fill_input(buff, lst);
}
