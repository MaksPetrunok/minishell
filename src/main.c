/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 17:00:30 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 20:57:58 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

void	sh_loop(void)
{
	char	*input;
	int		run;

	run = 1;
	while (run)
	{
		upd_binary_lst();
		show_prompt();
		if (get_input(&input, 0) > 0)
		{
			if ((input = combine_input(input)) != NULL)
				run = process_input(input);
		}
		else if (g_shell.interactive)
		{
			if (g_shell.inp_state == S_HD)
				add_newline();
			write(1, "\n", 1);
		}
		run = g_shell.interactive || *input;
		free((void *)input);
	}
}

int		main(int ac, char **av, char **ev)
{
	(void)av;
	(void)ac;
	if (!init_input(ac, av))
		return (1);
	if (init_shell(ev) != 0)
	{
		ft_dprintf(2, "cannot launch shell, failed to allocate memory\n");
		return (EXIT_ERR);
	}
	sh_loop();
	exit_shell();
	return (0);
}
