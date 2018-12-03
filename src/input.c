//header

#include "minishell.h"

#define TAB		0x9
#define CTRL_D	0x4
#define	LEFT	0x445b1b
#define RIGHT	0x435b1b
// not used yet
#define UP		0x415b1b
#define DOWN	0x425b1b
#define	ALT_RIGHT	0x661b
#define ALT_LEFT	0x621b
#define ALT_UP		0x415b1b //same as UP
#define ALT_DOWN	0x425b1b //same as DOWN
#define BACK_SP	0x7f
#define RETURN	0xa
#define DEL		0x7e335b1b
#define	CTRL_R	0x12

#define KEY_HANDLER_NUM	7

typedef	struct	s_key
{
	int			code;
	char		*cmd;
}				t_key;

int	v_putchar(int __attribute__((unused)) c)
{
	return (0);
}

char	*key_action(int	code)
{
	static t_key	table[KEY_HANDLER_NUM] = {
						{LEFT, "le"},
						{RIGHT, "nd"},
						{BACK_SP, "dc"},
						{RETURN, "return"},
						{DEL, "dc"},
						{TAB, "tab"},
						{CTRL_D, "ctrl+D"}};
	int				i;

	i = 0;
	while (i < KEY_HANDLER_NUM)
		if (table[i]->code == code)
			return (table[i]->cmd);
		else
			i++;
	return (0);
}

int	main()
{
	struct termios	term;
	char			*buff;

	if (tgetent(0, "xterm-256color") != 1)
		return (-1);
	if (tcgetattr(0, &term) != 0)
		return (-1);
	term.c_lflag &= ~(ECHO | ECHOE | ICANON);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, 0, &term) != 0)
		return (-1);

	//tputs(tgetstr("ti", &buff), 1, putch);
	ft_printf("test\n");
	tputs(tgetstr("le", &buff), 1, putch);
//	tputs(tgetstr("vi", &buff), 1, putch);

//	tputs(tgetstr("os", &buff), 1, putch);
//	tputs(tgetstr("co", &buff), 1, putch);
	tputs(tgetstr("im", &buff), 1, putch);
	ft_printf("BUFF=%p\n", buff);


	int		s;
	int		run = 1;
	char	*key;
	char	arr[5];

	while (run)
	{
		s = 0;
		read(0, &s, 8);

		t_pair	*t = table;
		while (t->id)
		{
			if (t->id == s)
			{
				if (t->id == LEFT || t->id == RIGHT || t->id == DEL)
					tputs(tgetstr(t->str, &buff), 1, putch);
				else if (t->id == BACK_SP)
				{
					tputs(tgetstr("le", &buff), 1, putch);
					tputs(tgetstr(t->str, &buff), 1, putch);
				}
				else
					tputs(t->str, 1, putch);
				break;
			}
			t++;
		}
		if (t->id != 0)
			continue ;

		tputs((char *)(&s), 1, putch);
		//tputs(tgetstr(s, &buff), 1, putch);
		if (s == '!')
			run = 0;
	}





	return (0);
}
