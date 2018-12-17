/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomp.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:59:13 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/13 20:51:05 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOCOMP_H
# define AUTOCOMP_H

void            fill_input(t_inp_buff *buff, t_list *head);
void			add_file(char *file, t_list **lst);
char			*convert_pattern(t_inp_buff *buff);
int				exec_complete(t_inp_buff *buff);
int				file_complete(t_inp_buff *buff);
int				auto_complete(t_inp_buff *buff);

/*
** aux.c
*/
int				sort(void *a, void *b);


#endif
