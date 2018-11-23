/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpetruno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 18:58:35 by mpetruno          #+#    #+#             */
/*   Updated: 2018/06/10 21:21:56 by mpetruno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*res;

	res = (t_list *)malloc(sizeof(t_list));
	if (res == 0)
		return (0);
	res->content = malloc(content_size);
	if (res->content == 0)
		return (0);
	res->next = 0;
	if (content == 0)
	{
		res->content_size = 0;
		res->content = 0;
	}
	else
	{
		res->content_size = content_size;
		res->content = ft_memcpy(res->content, content, content_size);
	}
	return (res);
}
