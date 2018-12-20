// header

#ifndef CURSOR_H
# define CURSOR_H

typedef struct	s_cusor
{
	int			row;
	int			col;
}				t_cursor;

int				init_cursor(void);
void			cur_mv_right(int insert);
void			cur_mv_left(void);

#endif
