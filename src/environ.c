/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 18:19:35 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/23 19:04:40 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "environ.h"
#include "err.h"

t_env	*g_myenv = 0;

void	init_environment(char **ev)
{
	char	**av;
	int		size;

	env_free(g_myenv);
	size = ft_arrsize((void **)ev) + 1;
	av = malloc(sizeof(char **) * size);
	if (!av || (g_myenv = malloc(sizeof(t_env))) == 0)
	{
		report_error(ERR_INITENV | ERR_MALLOC);
		exit(1);
	}
	g_myenv->capacity = size;
	g_myenv->av = av;
	while (size > 1 && *ev)
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
}

char	*get_var(const char *var_name)
{
	char	**ptr;
	char	*value;
	size_t	len;

	ptr = g_myenv->av;
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

	ptr = g_myenv->av;
	value = 0;
	len = ft_strlen(var_name);
	while (*ptr)
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
		else
			ptr++;
	if (0 && ptr - g_myenv->av > g_myenv->capacity)
		increase_env(g_myenv);
	return (0);
}
