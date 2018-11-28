/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 17:49:33 by mpetruno          #+#    #+#             */
/*   Updated: 2018/11/23 18:26:43 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
# define ENVIRON_H

# define ENV_BUFF_SIZE	64

typedef struct	s_env
{
	char		**av;
	int			capacity;
}				t_env;

extern t_env	*g_myenv;

void			init_environment(char **ev);
char			**get_env(void);
char			*get_var(const char *name);
int				set_var(const char *name, const char *value);
int				unset_var(const char *name);

int				increase_env(t_env *env);
void			env_free(t_env *env);
int				equals(const char *name, const char *entry);
char			*make_var_line(const char *name, const char *value, char *old);

#endif
