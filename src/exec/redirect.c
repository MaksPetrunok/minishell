/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 18:34:03 by mpetruno          #+#    #+#             */
/*   Updated: 2019/03/05 18:51:59 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define IS_WR(X) (X & S_IWUSR)
#define IS_RD(X) (X & S_IRUSR)

static int		check_fd(int fd, char io)
{
	struct stat	fst;

	if (fstat(fd, &fst) == -1)
		return (-1);
	if ((io == '<' && !IS_RD(fst.st_mode)) ||
		(io == '>' && !IS_WR(fst.st_mode)))
	{
		return (-1);
	}
	else
	{
		return (fd);
	}
}

static int		get_fd(char *rd, char *src)
{
	int	fd;

	if (ft_strequ(rd, "<"))
		fd = open(src, O_RDONLY);
	else if (ft_strequ(rd, ">"))
		fd = open(src, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (ft_strequ(rd, ">>"))
		fd = open(src, O_WRONLY | O_APPEND | O_CREAT, 0666);
	else if ((ft_strequ(rd, ">&") || ft_strequ(rd, "<&")) &&
		!ft_strequ(src, "-"))
	{
		if (ft_isnumeric(src))
			fd = check_fd(ft_atoi(src), *rd);
		else
			fd = -1;
	}
	else
		fd = 0;
	if (fd == -1)
		ft_dprintf(2, "cannot open %s\n", src);
	return (fd);
}

static void		aggregate_fd(int fd, char *src, int dst_fd)
{
	struct stat	st;

	if (ft_strequ(src, "-"))
		close(fd);
	else
	{
		if (fstat(fd, &st) == 0)
			dup2(dst_fd, fd);
		else
			ft_dprintf(2, "file descriptor %d not found\n", fd);
	}
}

static void		redirect(int fd, char *rd, char *src)
{
	int			pipe_fd[2];
	int			dst_fd;

	if ((dst_fd = get_fd(rd, src)) < 0)
		return ;
	if (ft_strequ(rd, ">") || ft_strequ(rd, ">>") || ft_strequ(rd, "<"))
	{
		dup2(dst_fd, fd);
		close(dst_fd);
	}
	else if (ft_strequ(rd, ">&") || ft_strequ(rd, "<&"))
		aggregate_fd(fd, src, dst_fd);
	else
	{
		pipe(pipe_fd);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		ft_dprintf(pipe_fd[1], "%s", src);
		close(pipe_fd[1]);
	}
}

void			redirect_io(char **io)
{
	char	*redir;
	int		fd;

	while (io && *io)
	{
		if (ft_isdigit(**io))
			fd = (int)ft_atoi(*io);
		else if (**io == '<')
			fd = 0;
		else
			fd = 1;
		redir = *io;
		while (ft_isdigit(*redir))
			redir++;
		redirect(fd, redir, *(io + 1));
		io += 2;
	}
}
