/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_addback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 11:03:19 by alienard          #+#    #+#             */
/*   Updated: 2020/08/05 15:07:43 by alienard         ###   ########.fr       */
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
		ref->head = new;
	new->prev = ref->tail;
	if (ref->tail)
		ref->tail->next = new;
	ref->tail = new;
}
