/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 17:00:30 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/18 13:20:52 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

int		process_input(char *input)
{
	t_token	*tkn_lst;
	t_ast	*root;
	int		run;

	run = 1;
	g_shell.run = 1;

	if (!g_shell.canonical)
		write(1, "\n", 1);
	tkn_lst = tokenize(input);

	ft_printf("INPUT: %s<<<\n", input);

	if ((root = parse(tkn_lst)) != NULL)
		run = execute_tree(root); // return proper value
	free_tree(root);
	root = NULL;
	tkn_lst = NULL;
	ft_printf("---------------------------------------\n");
	system("leaks minishell");
	ft_printf("---------------------------------------\n");
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
			write(1, "\n", 1);
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
