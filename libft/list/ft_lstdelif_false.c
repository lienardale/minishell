/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelif_false.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 11:28:01 by alienard          #+#    #+#             */
/*   Updated: 2020/09/16 15:46:56 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void		ft_lstdelif_false(t_list **alst, size_t (fct)(const char *))
{
	t_list	*prev;
	t_list	*next;
	t_list	*tmp;

	if (!alst || !*alst)
		return ;
	tmp = *alst;
	prev = NULL;
	next = tmp->next;
	while (tmp)
	{
		next = tmp->next;
		if (tmp && !fct(tmp->content) && prev)
		{
			ft_lstdelone(tmp, free);
			tmp = prev;
			prev->next = next;
		}
		else if (tmp && !fct(tmp->content) && !prev)
		{
			ft_lstdelone(tmp, free);
			*alst = next;
			prev = NULL;
			tmp = next;
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}
