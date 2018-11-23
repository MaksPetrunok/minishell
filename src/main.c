// header

#include "minishell.h"

int	process_cmd_lst(char **cmd_lst)
{
	char	**tmp;
	int		ret;

	ret = 1;
	tmp = cmd_lst;
	while (*cmd_lst && ret)
	{
		if (ft_strcmp("exit", *cmd_lst) == 0)
			ret = 0;
		// run current command
		if (ft_strchr(*cmd_lst, '='))
		{
			char *p = ft_strchr(*cmd_lst, '=');
			*p = '\0';
			set_var(*cmd_lst, p + 1);
		}
		else
		{
			char *s = get_var(*cmd_lst);
			ft_printf("%s\n", s);
			free(s);
		}


//		ft_printf("CMD: %s\n", *cmd_lst);
		// wait till command is completed
		cmd_lst++;
	}
	free_cmdlst(tmp);
	return (ret);
}

void	show_prompt(void)
{
	char	*usr;

	usr = get_var("USER");
	ft_printf("%s(%.*s): ", SHELL_NAME, (usr) ? 8 : 0, usr);
	free((void *)usr);
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

	if (ev)
		init_environment(ev);
	sh_loop();
	system("leaks minishell");
	return (0);
}
