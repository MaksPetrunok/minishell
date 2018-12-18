/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 17:49:33 by mpetruno          #+#    #+#             */
/*   Updated: 2018/12/18 14:31:47 by mpetruno         ###   ########.fr       */
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

t_env			*init_environment(char **ev);
char			**get_env(void);
char			*get_var(const char *name, t_env *env);
int				set_var(const char *name, const char *value, t_env *env);
int				unset_var(const char *name, t_env *env);

int				increase_env(t_env *env);
void			env_free(t_env *env);
int				equals(const char *name, const char *entry);
char			*make_var_line(const char *name, const char *value, char *old);

#endif
