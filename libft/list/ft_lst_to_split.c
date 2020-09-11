/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 18:42:58 by cdai              #+#    #+#             */
/*   Updated: 2020/09/11 15:34:30 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_lst_to_split(t_list *lst)
{
	char	**result;
	int		nb_str;
	int		i;
	
	nb_str = ft_lstsize(lst) + 1;
	result = ft_calloc(nb_str, sizeof(*result));
	i = 0;
	while (lst)
	{
		if (!(result[i] = ft_strdup((char*)lst->content)))
		{
			ft_free_split(result);
			return (NULL);
		}
		lst = lst->next;
		i++;
	}
	result[i] = 0; // useless cause of ft_calloc ?
	return (result);
}
