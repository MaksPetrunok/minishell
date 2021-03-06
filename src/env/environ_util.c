/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:39:10 by mpetruno          #+#    #+#             */
/*   Updated: 2019/01/06 17:33:00 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Increases size of environment buffer.
** Returns 1 on success or 0 on failure.
*/

int		increase_env(t_env *env)
{
	int		new_size;
	char	**av;

	new_size = env->capacity + ENV_BUFF_SIZE;
	av = (char **)ft_realloc((void *)(env->av),
					sizeof(char **) * env->capacity,
					sizeof(char **) * new_size);
	if (av == 0)
		return (0);
	env->av = av;
	env->capacity = new_size;
	return (1);
}

int		equals(const char *name, const char *entry)
{
	while (*name && *name == *entry)
	{
		name++;
		entry++;
	}
	if (*name == '\0')
		return ((*entry == '=') ? 1 : 0);
	return (0);
}

char	*make_var_line(const char *name, const char *value, char *old)
{
	char *tmp;

	if ((tmp = ft_strjoin3(name, "=", value)) == 0)
	{
		report_error(ERR_SETVAR | ERR_MALLOC);
		return (old);
	}
	free((void *)(old));
	return (tmp);
}

void	arr_free(void **arr)
{
	void	**ptr;

	if (arr == NULL)
		return ;
	ptr = arr;
	while (*ptr)
	{
		free((void *)(*ptr++));
	}
	free((void *)arr);
}

void	env_free(t_env *env)
{
	if (env == NULL)
		return ;
	arr_free((void *)env->av);
	free((void *)env);
}
