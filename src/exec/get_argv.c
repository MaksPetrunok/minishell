/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 18:34:03 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/28 16:56:28 by mpetruno         ###   ########.fr       */
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

static void	free_arrays(char ***av, char ***redir_lst)
{
	free((void *)(*av));
	free((void *)(*redir_lst));
	*av = NULL;
	*redir_lst = NULL;
}

static int	allocate_arrays(char ***av, char ***redir_lst, t_token *lst)
{
	int	size;

	size = 1;
	while(lst)
	{
		size++;
		lst = lst->next;
	}
	if (size == 1)
	{
		*av = NULL;
		*redir_lst = NULL;
		return (0);
	}
	if ((*av = malloc(sizeof(char **) * size)) == NULL ||
		(*redir_lst = malloc(sizeof(char **) * size)) == NULL)
	{
		free((void *)(*av));
		free((void *)(*redir_lst));
		ft_dprintf(2, "allocation error\n");
		return (0);
	}
	return (1);
}

static t_token	*add_redirection(t_token *io, char ***redir, int *index)
{
	if (io->data == NULL || io->next == NULL || io->next->data == NULL)
	{
		ft_dprintf(2, "cannot parse io redirection\n");
		if (io->next == NULL)
			return (io);
		else
			return (io->next);
	}
	*(*redir + *index) = io->data;
	*index += 1;
	*(*redir + *index) = io->next->data;
	*index += 1;
	*(*redir + *index) = NULL;
	return (io->next);
}

// if no arguments for av available - free av and redir_lst
// redir lst consists of sequense of T_IO_NUM->T_WORD->T_IO_NUM-T_WORD...
char	**get_arg_vector(t_token *lst, char ***redir_lst)
{
	char	**av;
	int		index_av;
	int		index_rd;

	expand_tokens(lst);
	if (allocate_arrays(&av, redir_lst, lst) == 0)
		return (NULL);
	index_av = 0;
	index_rd = 0;
	while (lst)
	{
		if (lst->type == T_ASSIGN)
			assign_var(lst->data);
		else if (lst->type == T_IO_NUM)
			lst = add_redirection(lst, redir_lst, &index_rd);
		else
			av[index_av++] = lst->data;
		lst = lst->next;
	}
	if (index_av == 0)
		free_arrays(&av, redir_lst);
	av[index_av] = NULL;
	*(*redir_lst + index_rd) = NULL;
	return (av);
}
