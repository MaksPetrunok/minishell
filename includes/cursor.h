// header

#ifndef CURSOR_H
# define CURSOR_H

typedef struct	s_cusor
{
	int			row;
	int			col;
}				t_cursor;

typedef struct	s_positions
{
	t_cursor	prompt;
	t_cursor	cmd;
	t_cursor	current;
}				t_positions;

int				init_cursor(void);
void			cur_mv_up(void);
void			cur_mv_down(void);
void			cur_mv_left(void);
void			cur_mv_right(void);

int				inp_movelw(t_inp_buff *buff, char *sym);
int				inp_moverw(t_inp_buff *buff, char *sym);

#endif
