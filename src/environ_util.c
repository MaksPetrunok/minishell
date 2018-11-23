// header

#include "libft.h"
#include "environ.h"
#include "err.h"

void	env_free(env_t *env)
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

env_t	*increase_env(env_t **env)
{
	int		new_size;
	env_t	*new;

	new_size = (*env)->capacity;
	new = malloc(sizeof(env_t));
	new->av = malloc(sizeof(char **) * new_size);
	new->capacity = new_size;
	return (new);
}
