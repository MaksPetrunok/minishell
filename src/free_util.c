// header

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

	if (arr == 0)
		return ;
	ptr = arr;
	while (*ptr)
		free((void *)(*ptr++));
	free((void *)arr);
}

void	env_free(t_env *env)
{
	if (!env)
		return ;
	arr_free((void *)env->av);
	free((void *)env);
}
