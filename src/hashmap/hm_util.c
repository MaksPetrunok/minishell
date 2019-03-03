/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 17:00:30 by mpetruno          #+#    #+#             */
/*   Updated: 2019/02/28 15:01:08 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"

unsigned long	hash(const char *str)
{
	unsigned long	hash;

	hash = 5381;
	while (*str)
		hash = ((hash << 5) + hash) + *str++;
	return (hash);
}

t_hment			*new_hmentry(const char *key, const char *value)
{
	t_hment	*new;
	char	*new_key;
	char	*new_val;

	new = malloc(sizeof(t_hment));
	new_key = ft_strdup(key);
	new_val = ft_strdup(value);
	if (!new || !new_key || !new_val)
	{
		free((void *)new);
		free((void *)new_key);
		free((void *)new_val);
		return (NULL);
	}
	new->prev = NULL;
	new->next = NULL;
	new->key = new_key;
	new->value = new_val;
	return (new);
}

void			del_hmentry(t_hment *ent)
{
	if (ent->prev)
		ent->prev->next = ent->next;
	if (ent->next)
		ent->next->prev = ent->prev;
	free((void *)(ent->key));
	free((void *)(ent->value));
	free((void *)ent);
}

void	hmap_print(t_hashmap *hmap)
{
	int	count_emp = 0;
	for (int i = 0; i < hmap->size; i++)
	{
		if (hmap->list[i] == NULL) {
			count_emp++;
			continue ;
		}
		ft_printf("%d:", i);
		t_hment *ent = hmap->list[i];
		while (ent) {
			ft_printf(" (%s, %s)", ent->key, ent->value);
			ent = ent->next;
		}
		ft_printf("\n");
	}
	ft_printf("Empty buckets: %d\n", count_emp);
}
