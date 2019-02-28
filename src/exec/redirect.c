/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 18:34:03 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/21 19:30:07 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
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
*/

#define IS_WR(X) (X & S_IWUSR)
#define IS_RD(X) (X & S_IRUSR)

static int		check_fd(int fd, char io)
{
	struct stat	fst;

ft_printf("CHECKING FD\n");
	if (fstat(fd, &fst) == -1)
		return (-1);
/*
ft_printf("Still check: %o\n", fst.st_mode);
ft_printf("Read permis: %o\n", S_IRUSR);
ft_printf("Writ permis: %o\n", S_IWUSR);
*/
	if ((io == '<' && !IS_RD(fst.st_mode)) ||
		(io == '>' && !IS_WR(fst.st_mode)))
	{
ft_printf("CheckFD=%d\n", -1);
		return (-1);
	}
	else
	{
ft_printf("CheckFD=%d\n", fd);
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
//			fd = open(src, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	}
	else
		fd = 0;
	if (fd == -1)
		ft_dprintf(2, "cannot open %s\n", src);
	else //
	ft_printf("FD=%d\n", fd);
	return (fd);
}

static void		redirect(int fd, char *rd, char *src)
{
	int	pipe_fd[2];
	int	dst_fd;
	struct stat	st;

	if ((dst_fd = get_fd(rd, src)) < 0)
		return ;
	if (ft_strequ(rd, ">") || ft_strequ(rd, ">>") || ft_strequ(rd, "<"))
	{
		dup2(dst_fd, fd);
		close(dst_fd);
	}
	else if (ft_strequ(rd, ">&") || ft_strequ(rd, "<&"))
	{
		if (ft_strequ(src, "-"))
		{
//ft_printf("Closing %d\n", fd);
			close(fd);
		}
		else 
		{
//ft_printf("Duplicate %d as %d\n", dst_fd, fd);
			if (fstat(fd, &st) == 0)
				dup2(dst_fd, fd);
			else
				ft_dprintf(2, "file descriptor %d not found\n", fd);
		}
	}
	else
	{
//ft_printf("redirecting HEREDOC: %s\n", src);
		pipe(pipe_fd);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		ft_dprintf(pipe_fd[1], "%s", src);
		close(pipe_fd[1]);
	}
}

void	redirect_io(char **io)
{
	char	*redir;
	int		fd;

	while (io && *io)
	{
//ft_printf("Redirect arguments:\n%s\n%s\n", *io, *(io + 1));
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
