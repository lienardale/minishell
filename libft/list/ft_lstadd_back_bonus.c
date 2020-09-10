/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard@student.42.fr <alienard>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 18:31:39 by alienard          #+#    #+#             */
/*   Updated: 2020/09/10 17:15:14 by alienard@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*i;

	if (!new)
		return ;
	if (!alst || !(*alst))
	{
		*alst = new;
		return ;
	}
	i = *alst;
	while (i->next)
		i = i->next;
	i->next = new;
}
