/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 13:14:03 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/18 11:06:44 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_variable(char *expr, t_env **env)
{
	char	*ptr;

	ptr = ft_strchr(expr, '=');
	*ptr = '\0';
	set_var(expr, ptr + 1, *env);
	return (1);
}

static int	process_flag(char **av, t_env **env)
{
	if (*(*av + 1) == 'i')
	{
		env_free(*env);
		*env = init_environment(0);
		return (1);
	}
	else if (*(*av + 1) == 'u' && *(av + 1) != NULL)
	{
		unset_var(*(av + 1), *env);
		return (2);
	}
	else
	{
		ft_dprintf(2,
			"usage: env [-i] [-u name] [name=value ...] [unility ...]\n");
		env_free(*env);
		*env = init_environment(0);
		return (ft_arrsize((void **)av));
	}
}

static int	launch_util(char **av, t_env **env)
{
	int		ret;

	while (*av)
	{
		if (**av == '-')
			av += process_flag(av, env);
		else if (ft_strchr(*av, '='))
			av += set_variable(*av, env);
		else
		{
			ret = execute(av, *env);
			env_free(*env);
			return (ret);
		}
	}
	return (0);
}

int			builtin_env(char **av)
{
	t_env	*env;
	int		i;

	if ((env = init_environment(g_shell.environ->av)) == NULL)
	{
		ft_dprintf(2, "env: cannot allocate environment copy\n");
		return (1);
	}
	if (!launch_util(av + 1, &env))
	{
		i = 0;
		while (env->av[i])
			ft_printf("%s\n", env->av[i++]);
		env_free(env);
		g_shell.last_ret = 0;
	}
	return (1);
}
