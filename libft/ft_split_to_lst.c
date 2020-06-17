/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_to_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 16:13:09 by cdai              #+#    #+#             */
/*   Updated: 2020/06/16 14:57:37 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_split_to_lst(char **strs)
{
	t_list	*result;
	int		i;

	i = 0;
	result = 0;
	while (strs[i])
	{
		if (!result)
			result = ft_lstnew(ft_strdup(strs[i]));
		else
			ft_lstadd_back(&result, ft_lstnew(ft_strdup(strs[i])));
		i++;
	}
	return (result);
}
