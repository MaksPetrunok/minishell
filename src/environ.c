/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 18:19:35 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/10 00:38:34 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell shell;

static char	**duplicate_env(char **env, int size)
{
	char	**copy;
	int		i;

	if ((copy = (char **)malloc(sizeof(char **) * size)) == NULL)
		return (0);
//ft_printf("sizeof copy = %ld\n", sizeof(char **) * size);
	i = 0;
	while (i < size - 1)
	{
		if ((copy[i] = ft_strdup(*env++)) == 0)
		{
			arr_free((void **)copy);
			return (0);
		}
//ft_printf("%p	copy[%d]=%s\n", &copy[i], i, copy[i]);
		i++;
	}
	copy[i] = 0;
	return (copy);
}

t_env	*init_environment(char **ev)
{
	t_env	*new_env;
	char	**new_av;
	int		size;

	if (ev != NULL)
		size = ft_arrsize((void **)ev) + 1;
	else
		size = 1;
//ft_printf("initial env arr size = %d\n", size);
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

char *get_var(const char *var_name)
{
	char **ptr;
	char *value;
	size_t len;

	ptr = shell.environ->av;
	value = 0;
	len = ft_strlen(var_name);
	while (*ptr)
	{
		if (equals(var_name, *ptr))
		{
			value = *ptr + len + 1;
			break;
		}
		ptr++;
	}
	return (value);
}

int unset_var(const char *name)
{
	char **ptr;

	if (!name)
		return (-1);
	ptr = shell.environ->av;
	while (*ptr)
	{
		if (equals(name, *ptr))
		{
			free((void *)(*ptr));
			*ptr++ = 0;
			break;
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

int set_var(const char *var_name, const char *var_value)
{
	char **ptr;
	int index;

	var_value = (var_value == 0) ? "" : var_value;
	ptr = shell.environ->av;
	while (*ptr)
		if (equals(var_name, *ptr))
		{
			*ptr = make_var_line(var_name, var_value, *ptr);
			return (1);
		}
		else
			ptr++;
	index = ptr - shell.environ->av;
	if (index >= shell.environ->capacity - 1)
		if (increase_env(shell.environ) == 0)
		{
			report_error(ERR_SETVAR | ERR_MALLOC);
			return (0);
		}
	ptr = shell.environ->av;
	ptr[index] = make_var_line(var_name, var_value, ptr[index]);
	ptr[++index] = 0;
	return (1);
}
