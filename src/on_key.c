/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 10:12:24 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/05 16:00:45 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	term_cursor_move(int code)
{
	if (code == K_LEFT)
		tconf("le");
	else if (code == K_RIGHT)
		tconf("nd");
}

void	term_delete(int code)
{
	if (code == K_BACK_SP)
		tconf("le");
	tconf("dc");
}

void	term_print(long code)
{
	char	*s;

	s = (char *)(&code);
	techo(" ");
	tconf("le");
	unset_keyboard();
	ft_printf("%s", s);
	init_keyboard();
}

void	term_ignore(int UNUSED code)
{
	return ;
}
