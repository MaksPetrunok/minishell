/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 17:00:30 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/28 15:01:08 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *usage[10] =
{
    US_CD,
    US_ECHO,
    US_SETENV,
    US_UNSETENV,
    US_ENV,
    US_EXIT,
    US_UI
};

Shell syntax supports the following command delimiters:
; - commands executed in order they are written,
| - pipeline redirects output of command to the input of next command,
|| - logical or,
&& - logical and.
The following I/O redirections supported: >, <, >>, <<.
To stop running process, or clear input command - use Ctrl+C.
Shell supports the following builtin functions: echo, pwd, cd, env, setenv, unsetenv, exit.
To see builtin command usage use the following syntax:
help [builtin name].
To see input editing hotkeys type
help ui
