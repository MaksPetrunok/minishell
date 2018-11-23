// header

#include "libft.h"
#include "environ.h"
#include "err.h"

void	env_free(t_env *env)
{
	char	**ptr;

	if (!env)
		return ;
	ptr = env->av;
	while (*ptr)
	{
		free((void *)(*ptr));
		ptr++;
	}
	free((void *)env);
}

void	increase_env(t_env *env)
{
	int		new_size;
	char	**av;

	new_size = env->capacity + ENV_BUFF_SIZE;
	av = malloc(sizeof(char **) * new_size);

	g_myenv->capacity = new_size;
}
