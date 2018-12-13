/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 09:44:43 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/13 20:00:17 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# define K_LEFT			0x445b1b
# define K_RIGHT		0x435b1b
# define K_CTRL_D		0x4
# define K_TAB			0x9
# define K_RETURN		0xa
# define K_BACK_SP		0x7f
# define K_DEL			0x7e335b1b

# define K_CTRL_R		0x12
# define K_UP			0x415b1b
# define K_DOWN			0x425b1b
# define K_ALT_RIGHT	0x661b
# define K_ALT_LEFT		0x621b

# define KEY_NUM			13
# define INPUT_BUFF_SIZE	1
# define TAB_SIZE			4
# include <dirent.h>

typedef struct	s_inp_buff
{
	long		*data;
	int			pos;
	int			len;
	int			size;
}				t_inp_buff;

typedef int	(*t_key_act)(t_inp_buff **buff, int key_code);

typedef	struct	s_key
{
	int			code;
	t_key_act	on_key_act;
}				t_key;

int				init_keyboard(void);
int				unset_keyboard(void);
int				myputchar(int c);
int				techo(char *s);
int				tconf(char *s);

/*
** Input buffer manipulation functions.
*/
int				inp_insert(t_inp_buff **buff, int key_code);
int				inp_move(t_inp_buff **buff, int key_code);
int				inp_delete(t_inp_buff **buff, int key_code);
int				inp_autocomp(t_inp_buff **buff, int key_code);
int				inp_exit(t_inp_buff **buff, int key_code);
int				inp_ignore(t_inp_buff **buff, int key_code);
int				inp_delete(t_inp_buff **buff, int key_code);

/*
** Terminal visualisation functions.
*/
void			term_cursor_move(int code);
void			term_delete(int code);
void			term_print(long code);
void			term_ignore(int code);

t_inp_buff		*init_input_buff(void);
int				increase_input_buff(t_inp_buff **buff);
void			shift(t_inp_buff *buff, int direction);
void			input_buff_free(t_inp_buff *buff);
char			*utf_to_str(long *data, int size);
int				auto_complete(t_inp_buff **buff);
int				get_input(char **str);

#endif
