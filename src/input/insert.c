// header

#include "minishell.h"

static int			increase_buff(t_inp_buff *buff)
{
	int		new_size;
	size_t	new_bytes;
	size_t	old_bytes;
	char	**new_data;

	new_size = buff->size + INP_BUFF_SIZE;
	old_bytes = buff->size * sizeof(char **);
	new_bytes = new_size * sizeof(char **);
	new_data = ft_realloc((void *)(buff->data), old_bytes, new_bytes);
	if (new_data == buff->data || new_data == NULL)
		return (0);
	buff->data = new_data;
	buff->size = new_size;
	return (1);
}

int	inp_insert(t_inp_buff *buff, char *sym)
{
	int	i;

	if (buff->len >= buff->size - 1)
		if (!increase_buff(buff))
		{
			ft_dprintf(2, "\nfailed to increase input buffer\n");
			return (0);
		}
	i = buff->len;
	while (i >= buff->pos)
	{
		buff->data[i + 1] = buff->data[i];
		i--;
	}
	if ((buff->data[buff->pos] = ft_strdup(sym)) == NULL)
		return (0);
//ft_printf("data[%d]=%s\n", buff->pos, buff->data[buff->pos]);
	buff->pos++;
	buff->len++;
	i = buff->pos - 1;
	while (buff->data[i])
		ft_printf("%s", buff->data[i++]);
	tconf("ce");
	while (i-- > buff->pos)
		tconf("le");
	return (1);
}
