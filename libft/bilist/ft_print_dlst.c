/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_dlst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 11:05:47 by alienard          #+#    #+#             */
/*   Updated: 2020/08/30 15:42:13 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "list.h"
#include "libftprintf.h"

void	ft_print_dlst(t_dlist *dlst, char *str)
{
	int i;

	i = 0;
	ft_printf("--- %d nodes ---\n", ft_len_dlst(dlst));
	if (str)
		ft_printf("| %s\n", str);
	while (dlst)
	{
		ft_printf("| %d | \"%s\" (p='%s'|n='%s')\n",
			i++, dlst->data,
			dlst->prev ? dlst->prev->data : "",
			dlst->next ? dlst->next->data : "");
		dlst = dlst->next;
	}
	ft_printf("---------------\n\n");
}
