// header

// BEFORE RELEASE:
// Make output buffer in ft_printf from static to dynamic.
// Instead of flushing buffer to fd when it's full - reallocate new buffer
// and copy old buffer to new, continue filling increased buffer.
// Output should be printed only one time.
// Think about flushing the buffer when its size reaches some value, i.e. 10kB.

#include "minishell.h"

pid_t	g_child = 0;

int	process_cmd_lst(char **cmd_lst)
{
	char	**tmp;
	char	**tokens;
	int		ret;
	func_type	bf;

	ret = 1;
	tmp = cmd_lst;
	while (*cmd_lst && ret)
	{
		tokens = tokenize(*cmd_lst, " \t");
//		if (*tokens == 0)
//			continue ;
		if (*tokens)
		{
			if ((bf = get_builtin(*tokens)) != 0)
				ret = bf(tokens);
			else
				ret = execute(tokens);
		}
		free((void *)tokens);
		cmd_lst++;
	}
	free_cmdlst(tmp);
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
			ft_printf("%s:%s$", SHELL_NAME, cwd);
		free((void *)tmp);
		return ;
	}
	if (ft_strstr(cwd, tmp) == cwd)
		ft_printf("\x1b[1m%s:\x1b[94m~%s\x1b[0m$ ", SHELL_NAME, cwd + ft_strlen(tmp));
	else
		ft_printf("\x1b[1m%s:\x1b[94m%s\x1b[0m$ ", SHELL_NAME, cwd);
	free((void *)tmp);
}

void	sh_loop()
{
	char **cmd_lst;
	int		run;

	run = 1;
	while (run)
	{
		show_prompt();
		cmd_lst = get_input();
		run = process_cmd_lst(cmd_lst);
	}
}

int		main(int ac, char **av, char **ev)
{
	if (ac)
		ac = 0;
	if (av)
		av = 0;

	signal(SIGINT, sh_sig_handler);
	if (ev)
		init_environment(ev);
	sh_loop();
	return (0);
}
