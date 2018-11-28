// header

#include "minishell.h"

int	builtin_echo(char **av)
{
	av[1] = (av[1] == 0) ? "" : av[1];
	while (*(++av))
	{
		if (*(av + 1))
			ft_printf("%s ", *av);
		else
			ft_printf("%s\n", *av);
	}
	return (1);
}
