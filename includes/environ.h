


#ifndef ENV_H
# define ENV_H

# define ENV_BUFF_SIZE	64

typedef struct	env_s
{
	char		**av;
	int			capacity;
}				env_t;

void	init_environment(char **ev);
env_t	*increase_env(env_t **env);
void	env_free(env_t *env);
char	*get_var(const char *name);
int		set_var(const char *name, const char *value);

#endif
