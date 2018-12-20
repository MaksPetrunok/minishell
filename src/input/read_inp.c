/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_inp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 13:52:12 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/20 20:14:42 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

static t_inp_buff	*init_inp_buff(void)
{
	t_inp_buff	*buff;

	if ((buff = malloc(sizeof(t_inp_buff))) == NULL)
		return (NULL);
	if ((buff->data = malloc(sizeof(char **) * INP_BUFF_SIZE)) == NULL)
	{
		free((void *)buff);
		return (NULL);
	}
	buff->data[0] = NULL;
	buff->pos = 0;
	buff->len = 0;
	buff->size = INP_BUFF_SIZE;
	return (buff);
}

char				*inp_to_str(char **inp)
{
	char	*inp_str;
	int		len;
	int		i;
	int		j;
	int		k;

	i = 0;
	len = 0;
	while (inp[i])
		len += ft_strlen(inp[i++]);
	if ((inp_str = malloc(len + 1)) == NULL)
		return (NULL);
	i = 0;
	k = 0;
	while (inp[i])
	{
		j = 0;
		while (inp[i][j])
			inp_str[k++] = inp[i][j++];
		i++;
	}
	inp_str[k] = '\0';
	return (inp_str);
}

void				inp_buff_free(t_inp_buff *buff)
{
	int	i;

	i = 0;
	while (i < buff->len)
		free((void *)(buff->data[i++]));
	free((void *)(buff->data));
	free((void *)buff);
}

static void			read_input(t_inp_buff *buff, int fd)
{
	char	sym[SYM_SIZE + 1];
	int		i;

	i = 0;
	while (1)
	{
		i = 0;
		while (i <= SYM_SIZE)
			sym[i++] = '\0';
		read_symbol(sym, fd);
		if (ft_strequ(sym, K_RETURN))
			break ;
		else if (*sym && (*sym < 32 || *sym == 127))
			inp_control(buff, sym);
		else if (*sym)
			inp_insert(buff, sym);
	}
	while (buff->pos++ < buff->len)
		cur_mv_right();
}

/*
** Reads user input and assigns read string to *inp_str.
** If any input has been read returns value > 0. If no input
** read - sets *inp_str to NULL and returns 0.
*/

int					get_input(char **inp_str, int fd)
{
	t_inp_buff	*inp_buff;
	int			len;

	if (g_shell.canonical)
	{
		return (get_next_line(fd, inp_str));
	}
	if ((inp_buff = init_inp_buff()) == NULL)
	{
		*inp_str = NULL;
		return (0);
	}
	g_shell.input = inp_buff;
	read_input(inp_buff, fd);
	*inp_str = inp_to_str(inp_buff->data);
	len = inp_buff->len;
	inp_buff_free(inp_buff);
	g_shell.input = NULL;
	return (len);
}
