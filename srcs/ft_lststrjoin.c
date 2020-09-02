/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lststrjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 11:48:07 by cdai              #+#    #+#             */
/*   Updated: 2020/09/02 17:21:02 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_lststrjoin(t_list *lst, char *inter)
{
	char	*result;
	char	*temp;

	result = 0;
	while (lst)
	{
		if (result)
		{
			temp = result;
			result = ft_strjoin(temp, inter);
			free(temp);
			temp = result;
			result = ft_strjoin(temp, (char*)lst->content);
			free(temp);
		}
		else
			result = ft_strjoin(inter, (char*)lst->content);
		lst = lst->next;
	}
	return (result);
}
