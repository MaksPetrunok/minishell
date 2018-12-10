/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 22:47:07 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/10 00:00:10 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tknlst_free(t_token *lst)
{
	t_token	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free((void *)(lst->data));
		free((void *)lst);
		lst = tmp;
	}
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
//	int	i;

	if (env == NULL)
		return ;
//	i = 0;
//	while (env->av[i])
//		free((void *)(env->av[i++]));
	arr_free((void *)env->av);
	free((void *)env);
}
