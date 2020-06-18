/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_between.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 08:15:50 by cdai              #+#    #+#             */
/*   Updated: 2020/06/11 09:07:01 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lstdel_notfirst(t_list *temp, void *content, void (*del)(void*))
{
	t_list *previous;
	t_list *next;

	previous = temp;
	temp = temp->next;
	while (temp)
	{
		next = temp->next;
		if (temp->content == content)
		{
			ft_lstdelone(temp, del);
			previous->next = next;
			break;
		}
		previous = temp;
		temp = temp->next;
	}
}

void	ft_lstdel_between(t_list **alst, void *content, void (*del)(void*))
{
	t_list *temp;
	t_list *next;
	
	if (!alst || !*alst)
		return ;
	temp = *alst;
	next = temp->next;
	if (temp->content == content)
	{
		ft_lstdelone(temp, del);
		*alst = next;
	}
	else
		ft_lstdel_notfirst(temp, content, del);
}
