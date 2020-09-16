/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_before.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 18:12:07 by cdai              #+#    #+#             */
/*   Updated: 2020/09/16 17:40:58 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_before(t_list **alst, t_list *new, t_list *next)
{
	t_list	*temp;
	t_list	*previous;

	temp = *alst;
	previous = NULL;
	while (temp)
	{
		if (temp->content == next->content)
		{
			if (previous)
				previous->next = new;
			else
				*alst = new;
			new->next = temp;
			return ;
		}
		previous = temp;
		temp = temp->next;
	}
	previous->next = new;
}
