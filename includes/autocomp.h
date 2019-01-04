/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomp.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 19:59:13 by mpetruno          #+#    #+#             */
/*   Updated: 2019/01/04 21:05:51 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOCOMP_H
# define AUTOCOMP_H

void	print_options(t_list *lst);
void	refresh_ui(t_inp_buff *buff, t_list *head);
void	add_file(char *file, t_list **lst, int is_dir);
char	*convert_pattern(t_inp_buff *buff);
int		auto_complete(t_inp_buff *buff);
int		sort(void *a, void *b);
void	get_bin_lst(t_inp_buff *buff, t_list **lst);

int		exec_complete(t_inp_buff *buff);
int		file_complete(t_inp_buff *buff);

#endif
