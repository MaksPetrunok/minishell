/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 15:46:28 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/28 15:46:30 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

typedef struct s_dlist	t_dlist;

struct		s_dlist
{
	char	*str;
	t_dlist	*prev;
	t_dlist	*next;
};

typedef struct	s_history
{
	t_dlist		*stack;
	t_dlist		*iter;
	char		*tmp;
}				t_history;

int		init_history(void);
void	free_history(void);
int		history_add(char *cmd);
int		inp_hist_prev(t_inp_buff *buff, char *sym);
int		inp_hist_next(t_inp_buff *buff, char *sym);

#endif
