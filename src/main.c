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
//t_state_trans	g_fsm_table;
int	process_cmd_lst(char **cmd_lst)
{
	char	**tmp;
	char	**tokens;
	int		ret;
	t_func	bf;

	ret = 1;
	tmp = cmd_lst;
	while (*cmd_lst && ret)
	{
		tokens = tokenize_split(*cmd_lst, " \t");
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
		ft_printf("\x1b[1m%s:\x1b[94m~%s\x1b[0m$ ",
			SHELL_NAME, cwd + ft_strlen(tmp));
	else
		ft_printf("\x1b[1m%s:\x1b[94m%s\x1b[0m$ ", SHELL_NAME, cwd);
	free((void *)tmp);
}


#include <stdio.h>
char *type(enum e_signal sig) // for tests
{
        char *type[8] = {
                "GEN ",
                "VARN",
                "EXPR",
                "ESC ",
                "QUO ",
                "DQUO",
                "SPA ",
                "SEMI"
        };
        return (type[sig]);
}
/*
static void print_lst(t_list *lst)
{
    char **av;
	int	i = 0;
    
    while (lst)
    {  
        av = (char **)(lst->content);
        while (*av)
            ft_printf("%d: %s\n", i++, *av++);
		i = 0;
        write(1, "\n", 1);
        lst = lst->next;
    }
}
*/
void	sh_loop()
{
//	char	**cmd_lst;
	t_list	*cmdlst;
	int		run;
	char	*input;

	run = 1;
	while (run)
	{
		show_prompt();
/*
//testing
		{
char *inp;
get_next_line(0, &inp);
if (inp == 0)
	continue;
t_token *lst = tokenize(inp, ft_strlen(inp));
t_list	*cmds = parse(lst);
print_lst(cmds);

ft_printf("----------------------------------------------------\n");
while (lst)
{
	if (ft_strcmp(lst->data, "exit") == 0)
		exit(0);
	printf(">>> type: %s, compl: %d, data: %s\n",
			type(lst->type),lst->complete, lst->data);
	lst = lst->next;
}
continue;
		}
//end testing
*/
		if (get_next_line(0, &input) != 1)
			continue;
		cmdlst = parse(tokenize(input, ft_strlen(input)));
//		cmd_lst = get_input();
		while (cmdlst) //rework to avoid leaks
		{
//			run = process_cmd_lst((char **)(cmdlst->content));
			run = execute((char **)(cmdlst->content));
			cmdlst = cmdlst->next;
		}
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
