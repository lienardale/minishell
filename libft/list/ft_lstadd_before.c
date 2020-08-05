/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_before.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 18:12:07 by cdai              #+#    #+#             */
/*   Updated: 2020/08/05 18:39:33 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	ft_lstadd_before(alst, new, NULL) == ft_lstadd_back(alst, new);
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
