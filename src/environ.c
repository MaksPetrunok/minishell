// header

#include "libft.h"
#include "environ.h"
#include "err.h"

static env_t	*get_env_vector(env_t *vector)
{
	static env_t	*environ;

	if (vector)
	{
		env_free(environ);
		environ = vector;
	}
	return (environ);
}

void	init_environment(char **ev)
{
	env_t	*env;
	char	**av;
	int		size;

	size = ft_arrsize((void **)ev) + 1;
	av = malloc(sizeof(char **) * size);
	if (!av || (env = malloc(sizeof(env_t))) == 0)
	{
		report_error(ERR_INITENV | ERR_MALLOC);
		exit(1);
	}
	env->capacity = size;
	env->av = av;
	while (*ev)
	{
		if ((*av = ft_strdup(*ev)) == 0)
		{
			report_error(ERR_INITENV | ERR_MALLOC);
			exit(1);
		}
		av++;
		ev++;
	}
	*av = 0;
	get_env_vector(env);
}

char	*get_var(const char *var_name)
{
	char	**ptr;
	char	*value;
	size_t	len;

	ptr = get_env_vector(0)->av;
	value = 0;
	len = ft_strlen(var_name);
	while (*ptr)
	{
		if (ft_strncmp(var_name, *ptr, len) == 0)
		{
			if ((value = ft_strdup(*ptr + len + 1)) == 0)
				report_error(ERR_MALLOC);
			break ;
		}
		ptr++;
	}
	return (value);
}

int		set_var(const char *var_name, const char *var_value)
{
	char	**ptr;
	char	*value;
	size_t	len;
	env_t	*e;

	e = get_env_vector(0);
	ptr = e->av;
	value = 0;
	len = ft_strlen(var_name);
	while (*ptr)
	{
		if (ft_strncmp(var_name, *ptr, len) == 0)
		{
// MAKE IT SAFE
			if ((value = ft_strjoin3(var_name, "=", var_value)) == 0)
				report_error(ERR_SETVAR | ERR_MALLOC);
			else
				free((void *)(*ptr));
			*ptr = value;
			return (1);
		}
		ptr++;
	}
	if (0 && ptr - get_env_vector(0)->av > get_env_vector(0)->capacity)
		increase_env(&e);
	
	return (0);
}
