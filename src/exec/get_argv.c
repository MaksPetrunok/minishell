/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 18:34:03 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/20 19:18:49 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		assign_var(char *str)
{
	char	*delim;

	delim = ft_strchr(str, '=');
	*delim = '\0';
	set_var(str, delim + 1, g_shell.environ);
}

static int		tknlst_size(t_token *lst)
{
	int	count;

	count = 0;
	while(lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

static t_token	*redirect(t_token *io)
{
	// do io redirection here
	return (io->next);
}


char	**get_arg_vector(t_token *lst)
{
	char	**av;
	int		index;

	if ((av = malloc(sizeof(char **) * tknlst_size(lst)) + 1) == NULL)
	{
		ft_dprintf(2, "allocation error\n");
		return (NULL);
	}
	index = 0;
	while (lst)
	{
		expand_token(lst);
ft_printf("READY TO ADD: %s\n", lst->data);
		if (lst->type == T_ASSIGN)
			assign_var(lst->data);
		else if (lst->type == T_IO_NUM)
			lst = redirect(lst);
		else
		{
ft_printf("adding... %s\n", lst->data);
			av[index++] = lst->data;
		}
		lst = lst->next;
	}
	av[index] = NULL;


for (int i=0; av[i] != NULL; i++)
	ft_printf("ARG[%d]=%s\n", av[i]);

	return (av);
}
