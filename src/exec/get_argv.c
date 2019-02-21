/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 18:34:03 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/21 19:30:07 by mpetruno         ###   ########.fr       */
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

#define IS_WR(X) ((X & S_IRWXU) == S_IWUSR)
#define IS_RD(X) ((X & S_IRWXU) == S_IRUSR)

static int		check_fd(int fd, char io)
{
	struct stat	fst;

	if (fstat(fd, &fst) == -1)
		return (-1);
	if ((io == '<' && !IS_RD(fst.st_mode)) ||
		(io == '>' && !IS_WR(fst.st_mode)))
		return (-1);
	else
		return (fd);
}

static int		get_fd(char *rd, t_token *src)
{
	int	fd;

	expand_token(src);
	if (ft_strequ(rd, "<"))
		fd = open(src->data, O_RDONLY);
	else if (ft_strequ(rd, ">"))
		fd = open(src->data, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (ft_strequ(rd, ">>"))
		fd = open(src->data, O_APPEND | O_CREAT, 0666);
	else if (ft_strequ(rd, ">&") || ft_strequ(rd, "<&"))
	{
		if (ft_isnumeric(src->data))
			fd = check_fd(ft_atoi(src->data), *rd);
		else
			fd = open(src->data, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	}
	else
		fd = 0;
	if (fd == -1)
		ft_dprintf(2, "cannot open %s\n", src->data);
	return (fd);
}

static void		perform_redirection(int	fd, char *rd, t_token *src)
{
	int	pipe_fd[2];
	int	dst_fd;

	if ((dst_fd = get_fd(rd, src)) < 0)
		return ;
	if (ft_strequ(rd, ">") || ft_strequ(rd, ">>") || ft_strequ(rd, "<"))
		dup2(dst_fd, fd);
	else if (ft_strequ(rd, ">&") || ft_strequ(rd, "<&"))
	{
		if (ft_strequ(src->data, "-"))
			close(dst_fd);
		else
			dup2(dst_fd, fd);
	}
	else
	{
		pipe(pipe_fd);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		ft_dprintf(pipe_fd[1], "%s", src->data);
		close(pipe_fd[1]);
	}
}


static t_token	*redirect(t_token *io)
{
	char	*redir;
	int		fd_ref;

	if (ft_isdigit(io->data[0]))
		fd_ref = ft_atoi(io->data);
	else if (io->data[0] == '<')
		fd_ref = 0;
	else
		fd_ref = 1;
	redir = io->data;
	while (ft_isdigit(*redir))
		redir++;
	perform_redirection(fd_ref, redir, io->next);

	// do io redirection here
	return (io->next);
}


char	**get_arg_vector(t_token *lst)
{
	char	**av;
	int		index;

	if ((av = malloc(sizeof(char **) * (tknlst_size(lst)) + 1)) == NULL)
	{
		ft_dprintf(2, "allocation error\n");
		return (NULL);
	}
	index = 0;
	while (lst)
	{
		expand_token(lst);
		if (lst->type == T_ASSIGN)
			assign_var(lst->data);
		else if (lst->type == T_IO_NUM)
			lst = redirect(lst);
		else
			av[index++] = lst->data;
		lst = lst->next;
	}
	av[index] = NULL;
	return (av);
}
