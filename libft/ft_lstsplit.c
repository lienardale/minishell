/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 11:01:16 by cdai              #+#    #+#             */
/*   Updated: 2020/05/11 14:11:09 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_lstsplit_add(t_list **result, char *str, int start, int i)
{
	t_list	*temp_lst;
	char	*temp_str;

	if (!(temp_str = ft_substr(str, start, i - start)))
		return (NULL);
	if (!(temp_lst = ft_lstnew(temp_str)))
		return (NULL);
	if (!*result)
		*result = temp_lst;
	else
		ft_lstadd_back(result, temp_lst);
	return (temp_lst);
}

t_list			*ft_lstsplit(char *str, char c)
{
	t_list	*result;
	int		i;
	int		word_start;

	i = 0;
	result = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		word_start = i;
		while (str[i] && str[i] != c)
			i++;
		if (!(ft_lstsplit_add(&result, str, word_start, i)))
		{
			ft_lstclear(&result, free);
			return (NULL);
		}
	}
	return (result);
}
