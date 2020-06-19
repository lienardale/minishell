/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_addfront.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 11:04:59 by alienard          #+#    #+#             */
/*   Updated: 2020/06/19 11:29:35 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "list.h"

void	ft_dslt_addfront(t_ref *ref, void *data)
{
	t_dlist	*new;

	if (!(new = ft_dlst_new_node(data)))
		return ;
	new->next = ref->head;
	new->prev = NULL;
	if (ref->head)
		ref->head->prev = new;
	ref->head = new;
}
