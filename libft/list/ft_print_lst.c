/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 15:41:41 by alienard          #+#    #+#             */
/*   Updated: 2020/08/30 15:44:16 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "list.h"
#include "libftprintf.h"

void	ft_print_lst(t_list *lst, char *str)
{
	int i;

	i = 0;
	ft_printf("--- %d nodes ---\n", ft_lstsize(lst));
	if (str)
		ft_printf("| %s\n", str);
	while (lst)
	{
		ft_printf("| %d | \"%s\" (n='%s')\n",
			i++, lst->content,
			lst->next ? lst->next->content : "");
		lst = lst->next;
	}
	ft_printf("---------------\n\n");
}
