
// header

#ifndef ERR_H
# define ERR_H

# define ERR_ALL	0xFF
# define ERR_MAIN	0xF0
# define ERR_AUX	0x0F

# define IS_ALL_ERR(X)				((X & ERR_MAIN) && (X & ERR_AUX))
# define IS_MAIN_ERR_ONLY(X)	((X & ERR_MAIN) && !(X & ERR_AUX))


# define ERR_INITENV	0x10
# define ERR_SETVAR		0x20

# define ERR_MALLOC	0x01

# define ESTR_MALLOC	"Failed to allocate memory."
# define ESTR_INITENV	"Cannot initialize environment."
# define ESTR_SETVAR	"Cannot set variable."

void	report_error(int err_code);


#endif
