// header

#include "minishell.h"

int	builtin_env(char __attribute__((unused))**av)
{
	char	**e;

	e = get_env();
	while (*e)
		ft_printf("%s\n", *(e++));
	return (1);
}
