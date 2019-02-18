/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:34:06 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/18 18:17:25 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// on success returns 1, on failure 0


static t_token		*get_next_token(t_token *tkn)
{
	t_token	*tmp;

	tmp = tkn->next;
	if (tmp)
		tmp->prev = tkn->prev;
	if (tkn->prev)
		tkn->prev->next = tmp;
	free((void *)tkn->data);
	free((void *)tkn);
	return (tmp);
}

static int	append_hd(t_token *hd, t_token *t, char *delim)
{
	char	*tmp;
	t_token	*start;

	start = t;
	while (t && t->next)
	{
		if (t->type == T_NEWLINE && ft_strequ(t->next->data, delim) &&
			(t->next->next == NULL || t->next->next->type == T_NEWLINE))
		{
			start->next = get_next_token(get_next_token(t));
			if (hd->next)
				hd->next->prev = hd;
			return (1);
		}
		tmp = hd->data;
		if (hd->data == NULL)
			hd->data = ft_strnew(0); //ft_strdup(t->data);
		else
			hd->data = ft_strjoin(hd->data, t->data);
		free((void *)tmp);
		t = get_next_token(t);
	}
	return (0);
}

static int	move_hd_into(t_token *tkn)
{
	char	*delim;
	t_token	*start;
	int		ret;

	if ((delim = ft_strdup(tkn->data)) == NULL)
	{
		ft_dprintf(2, "allocation error\n");
		return (0);
	}
	start = tkn;
	while (start)
		if (start->next && start->next->type == T_NEWLINE)
			break;
		else
			start = start->next;
	if (start == NULL)
	{
		free((void *)delim);
		return (0);
	}
ft_printf("HD START TKN=%s\n", start->data);
	free((void *)(tkn->data));
	tkn->data = NULL;
	ret = append_hd(tkn, start->next, delim);
	free((void *)delim);
	return (ret);
}

int	open_heredocs(t_token *lst)
{
	while (lst)
	{
		// check if current token is heredoc redirection
		if (lst->type == T_IO_NUM && ft_strstr(lst->data, "<<"))
		{
			// if it is heredoc redir and next token is not word - report error
			if (!lst->next || lst->next->type != T_WORD)
			{
				ft_dprintf(2, "syntax error after token '%s'\n", lst->data);
				return (0);
			}
			// if it's not possible to combine tokens into heredoc
			// continue input with prompt "heredoc>"
			// otherwise continue opening other heredocs
			if (!move_hd_into(lst->next))
				return (0);
		}
		lst = lst->next;
	}
	return (1);
}
