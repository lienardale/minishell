/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_reverse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 11:05:35 by alienard          #+#    #+#             */
/*   Updated: 2020/06/19 11:07:39 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "list.h"

void	ft_dlst_reverse(t_dlist **begin)
{
	t_dlist	*tmp;
	t_dlist	*current;

	tmp = NULL;
	current = *begin;
	while (current)
	{
		tmp = current->prev;
		current->prev = current->next;
		current->next = tmp;
		current = current->prev;
		if (tmp)
			*begin = tmp->prev;
	}
}
