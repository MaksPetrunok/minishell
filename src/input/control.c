// header

#include "minishell.h"

static t_key    g_table[KEY_NUM] = {
	{K_LEFT,		&inp_movel},
	{K_RIGHT,		&inp_mover},
	{K_BACK_SP,		&inp_backsp},
	{K_DEL,			&inp_delete},
	{K_TAB,			&inp_tab},
//	{K_CTRL_D,		&inp_exit},
//	{K_UP,			&inp_ignore},
//	{K_DOWN,		&inp_ignore},
//	{K_CTRL_R,		&inp_ignore},
//	{K_ALT_LEFT,	&inp_ignore},
//	{K_ALT_RIGHT,	&inp_ignore},
	{NULL,			&inp_ignore}
};

int	is_control(char *str)
{
	int	i;

	i = 0;
	while (g_table[i].code)
		if (ft_strstr(g_table[i].code, str) == g_table[i].code)
		{
			if (ft_strequ(g_table[i].code, str))
				return (2);
			else
				return (1);
		}
		else
			i++;
	return (0);
}

int	inp_tab(t_inp_buff *buff, char *sym)
{
	int	i;

	i = buff->pos;
	while (i >= 0)
	{
		if (buff->data[i] && buff->data[i][0] != ' ' && buff->data[i][0] != '\t')
		{
			//ft_printf("\nautocompletion\n");
			auto_complete(buff);
			return (1);
		}
		i--;
	}
	inp_insert(buff, sym);
	return (1);
}

int	inp_control(t_inp_buff *buff, char *sym)
{
	int	i;

	i = 0;
	while (g_table[i].code && ft_strcmp(g_table[i].code, sym))
		i++;
	return (g_table[i].action(buff, sym));
}
