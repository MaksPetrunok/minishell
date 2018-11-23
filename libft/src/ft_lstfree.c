/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 20:07:51 by mpetruno          #+#    #+#             */
/*   Updated: 2018/06/18 18:44:10 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstfree(t_list **alst)
{
	t_list	*tmp;

	if (!alst)
		return ;
	while (*alst != 0)
	{
		tmp = (*alst)->next;
		free((void *)((*alst)->content));
		free((void *)(*alst));
		*alst = tmp;
	}
}
