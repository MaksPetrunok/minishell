/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:38:47 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/30 23:19:19 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// BEFORE RELEASE:
// Make output buffer in ft_printf from static to dynamic.
// Instead of flushing buffer to fd when it's full - reallocate new buffer
// and copy old buffer to new, continue filling increased buffer.
// Output should be printed only one time.
// Think about flushing the buffer when its size reaches some value, i.e. 10kB.

#include "minishell.h"

pid_t	g_child = 0;

int	process_cmd(char **cmd_lst)
{
	int		ret;
	t_func	bf;

	ret = 1;
	if ((bf = get_builtin(*cmd_lst)) != 0)
		ret = bf(cmd_lst);
	else
		ret = execute(cmd_lst);
	arr_free((void **)cmd_lst);
	return (ret);
}

void	show_prompt(void)
{
	char	*tmp;
	char	cwd[5000];
	char	*is_wd;

	cwd[0] = '\0';
	is_wd = getcwd(cwd, 5000);
	if ((tmp = get_var("HOME")) == 0)
	{
		if (!is_wd)
			ft_printf("%s: ", SHELL_NAME);
		else
			ft_printf("\x1b[1m%s:\x1b[0;94m%s\x1b[0m$ ", SHELL_NAME, cwd);
		free((void *)tmp);
		return ;
	}
	if (ft_strstr(cwd, tmp) == cwd)
		ft_printf("\x1b[1m%s:\x1b[94m~%s\x1b[0m$ ",
			SHELL_NAME, cwd + ft_strlen(tmp));
	else
		ft_printf("\x1b[1m%s:\x1b[94m%s\x1b[0m$ ", SHELL_NAME, cwd);
	free((void *)tmp);
}

void	sh_loop()
{
	t_token	*tkn_lst;
	t_token	*tkn_ptr;
	char	*input;
	int		run;

	run = 1;
	while (run)
	{
		show_prompt();
		if (get_next_line(0, &input) == 1)
		{
			tkn_lst = tokenize(input);
			tkn_ptr = tkn_lst;
			while (tkn_ptr && run)
			{
				run = process_cmd(parse_cmd(&tkn_ptr));
				if (tkn_ptr && tkn_ptr->type == CH_SEMICOLON)
					tkn_ptr = tkn_ptr->next;
			}
			tknlst_free(tkn_lst);
		}
		else
			write(1, "\n", 1);
		free((void *)input);
	}
}

int		main(int ac, char **av, char **ev)
{
	if (ac)
		ac = 0;
	if (av)
		av = 0;

	setup_signals();
	if (ev)
		init_environment(ev);
	sh_loop();
	env_free(g_myenv);
	return (0);
}
