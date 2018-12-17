// header

#include "minishell.h"

int	putch(int c)
{
	return (write(1, &c, 1));
}

int	inp_movel(t_inp_buff *buff, char *sym)
{
	(void)sym;
	if (buff->pos == 0)
		return (0);
	buff->pos--;
	if (buff->data[buff->pos][0] == '\t')
		tconf("bt");
	else
		tconf("le");
	return (1);
}

int	inp_mover(t_inp_buff *buff, char *sym)
{
	(void)sym;
	if (buff->pos == buff->len)
		return (0);
	if (buff->data[buff->pos][0] == '\t')
		tconf("ta");
	else
		tconf("nd");
	buff->pos++;
	return (1);
}

int	inp_ignore(t_inp_buff *buff, char *sym)
{
	(void)buff;
	(void)sym;
	return (1);
}
