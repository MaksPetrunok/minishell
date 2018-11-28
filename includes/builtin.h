// header

#ifndef BUILTIN_H
# define BUILTIN_H

typedef	int	(*func_type)(char **);

func_type	get_builtin(const char *name);

int	builtin_exit(char **av);
int	builtin_pwd(char **av);
int	builtin_cd(char **av);
int	builtin_env(char **av);
int	builtin_setenv(char **av);
int	builtin_unsetenv(char **av);
int	builtin_echo(char **av);

#endif
