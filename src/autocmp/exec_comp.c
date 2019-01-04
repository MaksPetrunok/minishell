/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_comp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:34:43 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/18 13:57:05 by mpetruno         ###   ########.fr       */
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
	lst = 0;
	n = -1;
	while (names[++n])
		if (patt == 0)
			add_file(names[n], lst);
		else
		{
			i = 0;
			while (patt[i] && names[n][i] == patt[i])
				i++;
			if (i > 0 && names[n][i] && patt[i] == '\0')
				add_file(names[n] + i, lst);
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
	char	*str;

	match = get_execs(buff);
	head = match;
	while (match && ft_lstsize(head) > 1)
	{
		techo("\n --- ");
		techo((char *)(match->content));
		match = match->next;
	}
	if (ft_lstsize(head) > 1)
	{
		techo("\n");
		show_prompt();
		if (*(str = inp_to_str(buff->data)))
			techo(str);
		free((void *)str);
	}
	fill_input(buff, head);
	ft_lstfree(&head);
	return (1);
}
