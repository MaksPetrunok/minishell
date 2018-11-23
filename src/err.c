
// header

#include "err.h"
#include "libft.h"


char	*get_main_err(int code)
{
	if (code & ERR_INITENV)
		return (ESTR_INITENV);
	else if (code & ERR_SETVAR)
		return (ESTR_SETVAR);
	else
		return ("Error occured.");
}

char	*get_aux_err(int code)
{
	if (code & ERR_MALLOC)
		return (ESTR_MALLOC);
	else
		return ("Error occured.");
}

void	report_error(int code)
{
	if (IS_ALL_ERR(code))
		ft_printf("%s %s\n", get_main_err(code), get_aux_err(code));
	else if (IS_MAIN_ERR_ONLY(code))
		ft_printf("%s\n", get_main_err(code));
	else
		ft_printf("%s\n", get_aux_err(code));
}
