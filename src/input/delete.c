// header

#include "minishell.h"

int	inp_backsp(t_inp_buff *buff, char *sym)
{
	(void)sym;
	if (buff->pos == 0)
		return (0);
	buff->pos--;
	tconf("le");
	inp_delete(buff, sym);
	return (1);
}

int	inp_delete(t_inp_buff *buff, char *sym)
{
	int	i;

	(void)sym;
	if (buff->pos == buff->len)
		return (0);
	if (buff->data[buff->pos][0] == '\t')
		tconf("kt");
	else
		tconf("dc");
	free((void *)(buff->data[buff->pos]));
	i = buff->pos;
	while (i < buff->len)
	{
		buff->data[i] = buff->data[i + 1];
		i++;
	}
	buff->len--;
	return (1);
}
