/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 17:00:30 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/28 15:01:08 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

int		process_input(char *input)
{
	t_token	*tkn_lst;
	t_ast	*root;
	int		run;
	int		hd_status;

	g_shell.run = 1;

	if (!g_shell.canonical)
		write(1, "\n", 1);
	tkn_lst = tokenize(input);

//	ft_printf("INPUT: %s<<<\n", input);

	run = 1;
	root = NULL;
	if ((hd_status = open_heredocs(tkn_lst)) > 0)
	{
		if ((root = parse(tkn_lst)) != NULL)
			run = execute_tree(root); // return proper value
	}
	else if (hd_status == 0)
	{
		g_shell.const_input = ft_strdup(input);
		g_shell.inp_state = S_HD;
		tknlst_free(tkn_lst);
	}
	else
	{
		g_shell.inp_state = S_GEN;
		tknlst_free(tkn_lst);
	}
	free_tree(root);
	//tkn_lst = NULL;
/*
	ft_printf("-----------------------------------------------------------\n");
	system("leaks -quiet minishell");
	ft_printf("-----------------------------------------------------------\n");
*/
	return (run);
}

char	*combine_input(char *inp)
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

void	append_newline(void)
{
	char	*tmp;

	if (g_shell.const_input == NULL)
		return ;
	if ((tmp = ft_strjoin(g_shell.const_input, "\n")) == NULL)
		return ;
	free((void *)(g_shell.const_input));
	g_shell.const_input = tmp;
}

void	sh_loop(void)
{
	char	*input;
	int		run;

	run = 1;
	while (run)
	{
		show_prompt();
		if (get_input(&input, 0) > 0)
		{
			if ((input = combine_input(input)) != NULL)
				run = process_input(input);
		}
		else
		{
			if (g_shell.inp_state == S_HD)
				append_newline();
			write(1, "\n", 1);
		}
		free((void *)input);
	}
}

int		main(int ac, char **av, char **ev)
{
	(void)av;
	(void)ac;
	if (init_shell(ev) != 0)
	{
		ft_dprintf(2, "cannot launch shell, failed to allocate memory\n");
		return (EXIT_ERR);
	}
	sh_loop();
	exit_shell();
	return (0);
}
