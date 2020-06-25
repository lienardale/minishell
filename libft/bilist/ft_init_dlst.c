/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_dlst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 11:02:35 by alienard          #+#    #+#             */
/*   Updated: 2020/06/25 15:49:08 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "list.h"

void	ft_init_dlst(t_ref **dlst)
{
	if (!((*dlst) = ft_calloc(1, sizeof(t_ref))))
		return ;
	(*dlst)->head = NULL;
	(*dlst)->tail = NULL;
	(*dlst)->size = 0;
}
