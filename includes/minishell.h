
// header

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "environ.h"
# include "err.h"



# define	CMD_DELIM	';'

char	**get_input(void);
void	free_cmdlst(char **lst);

#endif
