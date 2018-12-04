/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 10:12:24 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/04 16:42:23 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	term_cursor_move(int code)
{
	char	**buff;

	buff = 0;
	if (code == K_LEFT)
		tputs(tgetstr("le", buff), 1, myputchar);
	else if (code == K_RIGHT)
		tputs(tgetstr("nd", buff), 1, myputchar);
}

void	term_delete(int code)
{
	char	**buff;

	buff = 0;
	if (code == K_BACK_SP)
		tputs(tgetstr("le", buff), 1, myputchar);
	tputs(tgetstr("dc", buff), 1, myputchar);
}

void	term_print(int code)
{
	tputs((char *)(&code), 1, myputchar);
}

void	term_ignore(int UNUSED code)
{
	return ;
}
