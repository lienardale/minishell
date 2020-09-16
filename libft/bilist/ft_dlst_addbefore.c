/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_addbefore.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 11:04:26 by alienard          #+#    #+#             */
/*   Updated: 2020/09/16 17:13:28 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "list.h"

void	ft_dlst_addbefore(t_ref *dlst, t_dlist *next, void *data)
{
	t_dlist	*new;

	if (!next)
		return ;
	if (!(new = ft_dlst_new_node(data)))
		return ;
	new->prev = next->prev;
	next->prev = new;
	new->next = next;
	if (new->prev)
		new->prev->next = new;
	else
		dlst->head = new;
}
