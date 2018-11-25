/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 17:49:43 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/23 17:51:51 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_H
# define ERR_H

# define ERR_ALL	0xFF
# define ERR_MAIN	0xF0
# define ERR_AUX	0x0F

# define IS_ALL_ERR(X)				((X & ERR_MAIN) && (X & ERR_AUX))
# define IS_MAIN_ERR_ONLY(X)	((X & ERR_MAIN) && !(X & ERR_AUX))

# define ERR_INITENV	0x10
# define ERR_SETVAR		0x20
# define ERR_ADDVAR		0x20 // add to .c file

# define ERR_MALLOC	0x01

# define ESTR_MALLOC	"Failed to allocate memory."
# define ESTR_INITENV	"Cannot initialize environment."
# define ESTR_SETVAR	"Cannot set variable."
# define ESTR_ADDVAR	"Cannot add new variable."

void	report_error(int err_code);

#endif
