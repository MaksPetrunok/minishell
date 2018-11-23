/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 17:49:54 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/23 18:35:16 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "environ.h"
# include "err.h"

# define SHELL_NAME	"smashmaybash"
# define CMD_DELIM	';'

char	**get_input(void);
void	free_cmdlst(char **lst);

#endif
