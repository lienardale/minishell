/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_last.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 12:19:31 by cdai              #+#    #+#             */
/*   Updated: 2020/05/12 12:29:24 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_last(t_list *lst)
{
	t_list	*previous;
	t_list	*last;

	previous = 0;
	last = 0;
	if (lst)
		previous = lst->next;
	else
		return ;
	if (previous)
		last = previous->next;
	else
	{
		ft_lstdelone(lst, free);
		return ;
	}
	while (last)
	{
		lst = previous;
		previous = last;
		last = last->next;
	}
	ft_lstdelone(previous, free);
	lst->next = NULL;
}
