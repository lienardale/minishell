/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_addback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 11:03:19 by alienard          #+#    #+#             */
/*   Updated: 2020/06/23 16:36:20 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "list.h"

void	ft_dlst_addback(t_ref *ref, void *data)
{
	t_dlist	*new;

	if (!(new = ft_dlst_new_node(data)))
		return ;
	new->next = NULL;
	if (!ref->head)
	{
		new->prev = NULL;
		return ;
	}
	ref->tail->next = new;
	new->prev = ref->tail;
	ref->tail = new;
}
