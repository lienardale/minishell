/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 11:05:05 by alienard          #+#    #+#             */
/*   Updated: 2020/09/16 17:13:41 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "list.h"

void	ft_dlst_del(t_ref *dlst)
{
	t_dlist	*tmp;
	t_dlist	*tmp2;

	if (!dlst || !dlst->head)
		return ;
	tmp = dlst->head;
	tmp2 = dlst->head;
	while (tmp)
	{
		tmp2 = tmp2->next;
		ft_dlst_delone(dlst, tmp);
		tmp = tmp2;
	}
}
