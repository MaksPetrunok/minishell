// header

#include "libft.h"

int	builtin_pwd(char __attribute__((unused))**av)
{
	char	cwd[4100];

	getcwd(cwd, 4100);
	ft_printf("%s\n", cwd);
	return (1);
}
