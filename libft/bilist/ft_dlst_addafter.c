/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_addafter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 10:50:02 by alienard          #+#    #+#             */
/*   Updated: 2020/09/16 17:13:20 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "list.h"

void	ft_dlst_addafter(t_ref *dlst, t_dlist *prev, void *data)
{
	t_dlist	*new;

	if (!prev)
		return ;
	if (!(new = ft_dlst_new_node(data)))
		return ;
	new->next = prev->next;
	prev->next = new;
	new->prev = prev;
	if (new->next)
		new->next->prev = new;
	else
		dlst->tail = new;
}
