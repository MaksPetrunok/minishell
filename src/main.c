// header

// BEFORE RELEASE:
// Make output buffer in ft_printf from static to dynamic.
// Instead of flushing buffer to fd when it's full - reallocate new buffer
// and copy old buffer to new, continue filling increased buffer.
// Output should be printed only one time.
// Think about flushing the buffer when its size reaches some value, i.e. 10kB.

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
		else if (ft_strchr(*cmd_lst, '='))
		{
			char *p = ft_strchr(*cmd_lst, '=');
			*p = '\0';
			set_var(*cmd_lst, p + 1);
		}
		else if (**cmd_lst == '!')
		{
			unset_var(*cmd_lst + 1);
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
	return (0);
}
