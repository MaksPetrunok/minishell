//header

#include <unistd.h>

enum 	t_state
{
	S_GENERAL,
	S_ESCAPE,
	S_QUOTE,
	S_DQUOTE
};

enum	t_signal
{
	CH_GENERAL,
	CH_ESCAPE,
	CH_QUOTE,
	CH_DQUOTE,
	CH_SPACE,
	CH_SEMICOLON
};

enum t_state	fsm_table[4][6] =
{
	[S_GENERAL][CH_GENERAL] = S_GENERAL,
	[S_GENERAL][CH_ESCAPE] = S_ESCAPE,
	[S_GENERAL][CH_QUOTE] = S_QUOTE,
	[S_GENERAL][CH_DQUOTE] = S_DQUOTE,
	[S_GENERAL][CH_SPACE] = S_GENERAL,
	[S_GENERAL][CH_SEMICOLON] = S_GENERAL,

	[S_ESCAPE][CH_GENERAL] = S_GENERAL,
 	[S_ESCAPE][CH_ESCAPE] = S_GENERAL,
	[S_ESCAPE][CH_QUOTE] = S_GENERAL,
	[S_ESCAPE][CH_DQUOTE] = S_GENERAL,
	[S_ESCAPE][CH_SPACE] = S_GENERAL,
	[S_ESCAPE][CH_SEMICOLON] = S_GENERAL,

	[S_QUOTE][CH_GENERAL] = S_QUOTE,
	[S_QUOTE][CH_ESCAPE] = S_QUOTE,
	[S_QUOTE][CH_QUOTE] = S_GENERAL,
	[S_QUOTE][CH_DQUOTE] = S_QUOTE,
	[S_QUOTE][CH_SPACE] = S_QUOTE,
	[S_QUOTE][CH_SEMICOLON] = S_QUOTE,

	[S_DQUOTE][CH_GENERAL] = S_DQUOTE,
	[S_DQUOTE][CH_ESCAPE] = S_DQUOTE,
	[S_DQUOTE][CH_QUOTE] = S_DQUOTE,
	[S_DQUOTE][CH_DQUOTE] = S_GENERAL,
	[S_DQUOTE][CH_SPACE] = S_DQUOTE,
	[S_DQUOTE][CH_SEMICOLON] = S_DQUOTE
};

enum t_signal	get_signal(char c)
{
	if (c == '\\')
		return (CH_ESCAPE);
	else if (c == '\'')
		return (CH_QUOTE);
	else if (c == '\"')
		return (CH_DQUOTE);
	else if (c == ' ')
		return (CH_SPACE);
	else if (c == ';')
		return (CH_SEMICOLON);
	else
		return (CH_GENERAL);
}

int	main(int ac, char **av)
{
	
	if (ac != 2)
		return (1);

	char	*s = av[1];
	enum t_state	st = S_GENERAL;
	while (*s)
	{
		enum t_signal sig = get_signal(*s);
		st = fsm_table[st][sig];
		if (st == S_GENERAL)
		{
			if (sig != CH_ESCAPE)
				write(1, s, 1);
		}
		else if (st == S_ESCAPE)
		{
			write(1, s, 1);
		}
		s++;
	}
	write(1, "\n", 1);
	return (0);
}
