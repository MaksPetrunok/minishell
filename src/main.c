/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 17:00:30 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/18 10:06:24 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

int		process_cmd(char **cmd_lst)
{
	int		ret;
	t_func	bf;

	ret = 1;
	if (!cmd_lst)
		return (1);
	if ((bf = get_builtin(*cmd_lst)) != 0)
		ret = bf(cmd_lst);
	else
		ret = execute(cmd_lst, g_shell.environ);
	arr_free((void **)cmd_lst);
	return (ret);
}

void	show_prompt(void)
{
	char	*tmp;
	char	cwd[5000];
	char	*is_wd;
	int		len;

ft_printf("YOYOYO: %p\n", g_shell.environ);
	switch_term_to(g_shell.term_typing);
	set_cursor(&(g_shell.positions.prompt));
	tconf("cd");
	cwd[0] = '\0';
	is_wd = getcwd(cwd, 5000);
	if (g_shell.inp_state != S_GEN || g_shell.inp_state != S_HSH)
	{
		if (g_shell.inp_state == S_SQT)
			len = ft_printf("quote> ");
		else if (g_shell.inp_state == S_DQT)
			len = ft_printf("dquote> ");
		else
			len = ft_printf("bquote> ");
		// careful here
	} else if ((tmp = get_var("HOME", g_shell.environ)) == 0 || *tmp == '\0')
	{
		if (!is_wd)
			len = ft_printf("%s: ", SHELL_NAME);
		else
			len = ft_printf("\x1b[1m%s:\x1b[0;94m%s\x1b[0m$ ",
				SHELL_NAME, cwd) - 15;
	}
	else if (ft_strstr(cwd, tmp) == cwd)
		len = ft_printf("\x1b[1m%s:\x1b[94m~%s\x1b[0m$ ",
			SHELL_NAME, cwd + ft_strlen(tmp)) - 13;
	else
		len = ft_printf("\x1b[1m%s:\x1b[94m%s\x1b[0m$ ",
			SHELL_NAME, cwd) - 13;
	g_shell.plen = len;
	g_shell.positions.cmd.col = len % g_shell.winsize.ws_col;
	g_shell.positions.cmd.row = g_shell.positions.prompt.row +
		len / g_shell.winsize.ws_col;
	g_shell.positions.current.col = g_shell.positions.cmd.col;
	g_shell.positions.current.row = g_shell.positions.cmd.row;
}

int		process_input(char *input)
{
	t_token	*tkn_lst;
	t_ast	*root;
	int		run;

	run = 1;
	g_shell.run = 1;
	if (!g_shell.canonical)
		write(1, "\n", 1);
	if (g_shell.inp_state == S_GEN || g_shell.inp_state == S_HSH)
		tkn_lst = tokenize(input);
	else
		tkn_lst = NULL;

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

void	sh_loop(void)
{
	char	*input;
	int		run;

	run = 1;
	while (run)
	{
		show_prompt();
		if (get_input(&input, 0) > 0)
			run = process_input(input);
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
