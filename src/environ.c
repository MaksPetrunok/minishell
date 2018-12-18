/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 18:19:35 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/18 14:23:50 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**duplicate_env(char **env, int size)
{
	char	**copy;
	int		i;

	if ((copy = (char **)malloc(sizeof(char **) * size)) == NULL)
		return (0);
	i = 0;
	while (i < size - 1)
	{
		if ((copy[i] = ft_strdup(*env++)) == 0)
		{
			arr_free((void **)copy);
			return (0);
		}
		i++;
	}
	copy[i] = 0;
	return (copy);
}

t_env		*init_environment(char **ev)
{
	t_env	*new_env;
	char	**new_av;
	int		size;

	if (ev != NULL)
		size = ft_arrsize((void **)ev) + 1;
	else
		size = 1;
	if ((new_av = duplicate_env(ev, size)) == 0)
		return (0);
	if ((new_env = malloc(sizeof(t_env))) == 0)
	{
		arr_free((void **)new_av);
		return (0);
	}
	new_env->av = new_av;
	new_env->capacity = size;
	return (new_env);
}

char		*get_var(const char *var_name, t_env *env)
{
	char	**ptr;
	char	*value;
	size_t	len;

	ptr = env->av;
	value = 0;
	len = ft_strlen(var_name);
	while (*ptr)
	{
		if (equals(var_name, *ptr))
		{
			value = *ptr + len + 1;
			break ;
		}
		ptr++;
	}
	return (value);
}

int			unset_var(const char *name, t_env *env)
{
	char **ptr;

	if (!name)
		return (-1);
	ptr = env->av;
	while (*ptr)
	{
		if (equals(name, *ptr))
		{
			free((void *)(*ptr));
			*ptr++ = 0;
			break ;
		}
		ptr++;
	}
	while (*ptr)
	{
		*(ptr - 1) = *ptr;
		*ptr++ = 0;
	}
	return (1);
}

int			set_var(const char *var_name, const char *var_value, t_env *env)
{
	char	**ptr;
	int		index;

	var_value = (var_value == 0) ? "" : var_value;
	ptr = env->av;
	while (*ptr)
		if (equals(var_name, *ptr))
		{
			*ptr = make_var_line(var_name, var_value, *ptr);
			return (1);
		}
		else
			ptr++;
	index = ptr - env->av;
	if (index >= env->capacity - 1)
		if (increase_env(env) == 0)
		{
			report_error(ERR_SETVAR | ERR_MALLOC);
			return (0);
		}
	ptr = env->av;
	ptr[index] = make_var_line(var_name, var_value, ptr[index]);
	ptr[++index] = 0;
	return (1);
}
