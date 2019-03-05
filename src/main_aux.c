/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 17:00:30 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 17:52:26 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	before_process_inp(int *run, t_ast **root)
{
	g_shell.run = 1;
	*run = 1;
	*root = NULL;
	if (!g_shell.canonical && g_shell.interactive)
		write(1, "\n", 1);
}

int			process_input(char *input)
{
	t_token	*tkn_lst;
	t_ast	*root;
	int		run;
	int		hd_status;

	before_process_inp(&run, &root);
	tkn_lst = tokenize(input);
	if ((hd_status = open_heredocs(tkn_lst)) > 0)
	{
		if ((root = parse(tkn_lst)) != NULL)
			run = execute_tree(root);
	}
	else if (hd_status == 0)
	{
		g_shell.const_input = ft_strdup(input);
		g_shell.inp_state = S_HD;
	}
	else
		g_shell.inp_state = S_GEN;
	if (root)
		free_tree(root);
	else
		tknlst_free(tkn_lst);
	return (run);
}

char		*combine_input(char *inp)
{
	char	*tmp;

	if (g_shell.const_input == NULL)
		return (inp);
	tmp = ft_strjoin3(g_shell.const_input, "\n", inp);
	if (tmp == NULL)
		ft_dprintf(2, "allocation error\n");
	free((void *)(g_shell.const_input));
	free((void *)inp);
	g_shell.const_input = NULL;
	return (tmp);
}

void		add_newline(void)
{
	char	*tmp;

	if (g_shell.const_input == NULL)
		return ;
	if ((tmp = ft_strjoin(g_shell.const_input, "\n")) == NULL)
		return ;
	free((void *)(g_shell.const_input));
	g_shell.const_input = tmp;
}
