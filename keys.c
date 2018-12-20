#include <unistd.h>
#include <stdio.h>
#include <term.h>

int	main()
{
	char	s[8];
	struct termios	term;
	struct termios	tref;

	tcgetattr(0, &term);
	tcgetattr(0, &tref);
	term.c_lflag &= ~(ECHO | ECHOE | ICANON);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, 0, &term);

	while (1)
	{
		int n = read(0, s, 8);
		printf("key: ");
		for (int i=0; i<n; i++)
			printf("\\x%hhx", s[i]);
		printf("\n");
	}
	tcsetattr(0, 0, &tref);
	return (0);
}
