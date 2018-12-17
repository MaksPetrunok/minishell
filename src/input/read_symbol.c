//header

#include "minishell.h"

void	read_symbol(char *buff, int fd)
{
	int	i;

	read(fd, buff, 1);
//ft_printf("READ %d\n", *buff);
	if (*buff == 27)
	{
		i = 2;
		read(fd, buff + 1, 1);
//ft_printf("ESC %c", *(buff + 1));
		while (i < SYM_SIZE && is_control(buff) == 1)
		{
			read(fd, buff + i++, 1);
//ft_printf("%c", *(buff + i - 1));
		}
//ft_printf("\n");
		if (!is_control(buff))
			*buff = '\0';
	}
	else if (*buff > 31)
		return ;
	else if ((*buff >> 5) == 0b110)
		read(fd, buff + 1, 1);
	else if ((*buff >> 4) == 0b1110)
		read(fd, buff + 1, 2);
	else if ((*buff >> 3) == 0b11110)
		read(fd, buff + 1, 3);
}
