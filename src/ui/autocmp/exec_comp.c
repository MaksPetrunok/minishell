/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_comp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:34:43 by mpetruno          #+#    #+#             */
/*   Updated: 2019/01/06 21:48:29 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_builtins(t_inp_buff *buff, t_list **lst)
{
	char	*names[BUILTINS_BUFF_SIZE];
	char	*patt;
	int		i;
	int		n;

	get_builtin_list(names);
	patt = convert_pattern(buff);
	n = -1;
	while (names[++n])
	{
		if (patt == NULL || *patt == '\0')
			add_file(names[n], lst, 0);
		else
		{
			i = 0;
			while (patt[i] && names[n][i] == patt[i])
				i++;
			if (i > 0 && names[n][i] && patt[i] == '\0')
				add_file(names[n], lst, 0);
		}
	}
	free((void *)patt);
}

t_list	*get_execs(t_inp_buff *buff)
{
	t_list	*lst;

	lst = NULL;
	get_builtins(buff, &lst);
	get_bin_lst(buff, &lst);
	return (lst);
}

int		exec_complete(t_inp_buff *buff)
{
	t_list	*match;
	t_list	*head;

	match = get_execs(buff);
	head = match;
	refresh_ui(buff, head);
	if (ft_lstsize(head) > 1)
		print_options(head);
	ft_lstfree(&head);
	return (1);
}
