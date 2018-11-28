// header

#include "libft.h"
#include "builtin.h"


static char	**get_builtin_list(char **list)
{
	short	i;

	i = 0;
	list[i++] = "exit";
	list[i++] = "pwd";
	list[i++] = "cd";
	list[i++] = "env";
	list[i++] = "setenv";
	list[i++] = "unsetenv";
	list[i++] = "echo";
	list[i] = 0;
	return (list);
}

static void	set_builtin_funcs(func_type *list)
{
	short	i;

	i = 0;
	list[i++] = &builtin_exit;
	list[i++] = &builtin_pwd;
	list[i++] = &builtin_cd;
	list[i++] = &builtin_env;
	list[i++] = &builtin_setenv;
	list[i++] = &builtin_unsetenv;
	list[i++] = &builtin_echo;
}

static int	get_builtin_index(const char *s)
{
	int	i;
	char	*names[10];

	get_builtin_list(names);
	i = 0;
	while (names[i])
	{
		if (ft_strcmp(s, names[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

func_type	get_builtin(const char *name)
{
	int	index;
	func_type	list[10];

	if (name == 0)
		return (0);
	set_builtin_funcs(list);
	index = get_builtin_index(name);
ft_printf("<debug>requested cmd: %s, builtin index=%d\n", name, index); // DELETE
	if (index == -1)
		return (0);
	return (list[index]);
}
