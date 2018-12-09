// header

#include "libft.h"
#include "input.h"
#include "environ.h"


typedef	struct		s_process
{
	pid_t			pid;
}					t_process;

typedef struct		s_cusor
{
	int				row;
	int				col;
}					t_cursor;

typedef struct		s_shell
{
	struct termios	*term_current;
	struct termios	*term_ref;
	t_inp_buff		*input;
	t_env			*environ;
	t_cursor		*cursor;
	t_list			*childs;
}					t_shell;

// provide getters for shell struct variables if necessary

int					init_shell(char **env);
void				exit_shell(void);

/*
** shell_init.c
*/
int					read_term_ref(void);
int					configure_term(void);
int					init_cursor(void);

/*
** shell_exit.c
*/
void				finish_child_processes(void);
int					restore_term_ref(void);