/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_new_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 11:05:28 by alienard          #+#    #+#             */
/*   Updated: 2020/06/19 11:06:32 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "list.h"

t_dlist	*ft_dlst_new_node(void *data)
{
	t_dlist *new;

	if (!(new = ft_calloc(1, sizeof(t_dlist))))
		return (NULL);
	new->data = data;
	return (new);
}
