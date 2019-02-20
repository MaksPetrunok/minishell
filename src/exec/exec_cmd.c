/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 13:08:57 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/20 19:20:46 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_wait(t_ast *node)
{
	ft_printf("WAIT: %s, pid=%d\n", node->tkn_lst->data, getpid());
	return (0);
}

#include <sys/ioctl.h>

int	exec_no_wait(t_ast *node)
{
	char	**av;

	ft_printf("NO WAIT: %s, pid=%d\n", node->tkn_lst->data, getpid());
	av = get_arg_vector(node->tkn_lst);

if (av == NULL)
	ft_printf("NULLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL\n");
else
	ft_printf("NOT NULLLLL\n");


ft_printf("Argument list:\n");
while(*av)
{
	ft_printf("%s\n", *av);
	av++;
}
ft_printf("End arg list\n");


	//--------------------------------------
	int	n = 0;
	ioctl(0, FIONREAD, &n);
	ft_printf("Bytes available: %d\n", n);

	while(n > 0)
	{
		char c;
		read(0, &c, 1);
		write(1, &c, 1);
		ioctl(0, FIONREAD, &n);
	}

	return (0);
}
