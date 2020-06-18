/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 07:42:10 by cdai              #+#    #+#             */
/*   Updated: 2020/05/13 07:51:49 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strs_sort(char **strs, int strs_len)
{
	int		i;
	char	*temp;

	i = 0;
	if (strs_len == 1)
		return (strs);
	while (i < strs_len - 1)
	{
		if (ft_strcmp(strs[i], strs[i + 1]) > 0)
		{
			temp = strs[i];
			strs[i] = strs[i + 1];
			strs[i + 1] = temp;
			i = 0;
		}
		i++;
	}
	return (strs);
}
