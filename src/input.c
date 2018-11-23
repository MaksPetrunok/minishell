
// header

#include "minishell.h"

char	**get_input(void)
{
	char	*inp;
	char	**res;

	inp = 0;
	get_next_line(0, &inp);
	if (inp == 0) // handle any errors here ?
		return (0);
	res = ft_strsplit(inp, CMD_DELIM); // handle special character \; - it must be ignored
										// only character ';' used for split
	if (res == 0 && inp != 0)
		exit(1); // indicate error
	free((void *)inp);
	return (res);
}

void	free_cmdlst(char **cmd)
{
	char **ref;

	if (cmd == 0)
		return ;
	ref = cmd;
	while (*cmd)
	{
		free((void *)(*cmd));
		cmd++;
	}
	free((void *)(ref));
}
