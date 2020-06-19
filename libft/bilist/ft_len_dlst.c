/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_dlst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 11:05:42 by alienard          #+#    #+#             */
/*   Updated: 2020/06/19 11:06:21 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "list.h"

size_t	ft_len_dlst(t_dlist *dlst)
{
	size_t	len;

	len = 0;
	while (dlst)
	{
		dlst = dlst->next;
		len++;
	}
	return (len);
}
