/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_delone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 11:05:17 by alienard          #+#    #+#             */
/*   Updated: 2020/09/11 13:42:49 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "list.h"

void	ft_dlst_delone(t_ref *dlst, t_dlist *del)
{
	if (dlst->head == NULL || !del)
		return ;
	if (dlst->head == del)
		dlst->head = del->next;
	if (del->next)
		del->next->prev = del->prev;
	if (del->prev)
		del->prev->next = del->next;
	if (del->data)
	{
		free(del->data);
		del->data = NULL;
	}
	free(del);
	del = NULL;
}
