/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 09:44:43 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/20 19:21:12 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# define K_LEFT			"\x1b\x5b\x44"
# define K_RIGHT		"\x1b\x5b\x43"
# define K_CTRL_D		"\x04"
# define K_TAB			"\x09"
# define K_RETURN		"\x0a"
# define K_BACK_SP		"\x7f"
# define K_DEL			"\x1b\x5b\x33\x7e"

# define K_CTRL_R		"\x12"
# define K_UP			"\x41\x5b\x1b"
# define K_DOWN			"\x42\x5b\x1b"
# define K_ALT_RIGHT	"\x66\x1b"
# define K_ALT_LEFT		"\x62\x1b"

# define KEY_NUM			13

# define INP_FD				0
# define INP_BUFF_SIZE		8
# define SYM_SIZE			4
# define TAB_SIZE			4

# include <dirent.h>

typedef struct	s_inp_buff
{
	char		**data;
	int			pos;
	int			len;
	int			size;
}				t_inp_buff;

typedef int	(*t_key_act)(t_inp_buff *buff, char *sym);

typedef	struct	s_key
{
	char		*code;
	t_key_act	action;
}				t_key;

/*
** terminal_outp.c
*/
int				tconf(char *s);
int				techo(char *s);

int				is_control(char *str);

char			*inp_to_str(char **inp);

int				inp_insert(t_inp_buff *buff, char *sym);
int				inp_control(t_inp_buff *buff, char *sym);
int				inp_movel(t_inp_buff *buff, char *sym);
int				inp_mover(t_inp_buff *buff, char *sym);
int				inp_delete(t_inp_buff *buff, char *sym);
int				inp_backsp(t_inp_buff *buff, char *sym);
int				inp_tab(t_inp_buff *buff, char *sym);
int				inp_autocomp(t_inp_buff *buff, char *sym);

int				inp_ignore(t_inp_buff *buff, char *sym);

void			read_symbol(char *buff, int fd);
int				get_input(char **str, int fd);

#endif
