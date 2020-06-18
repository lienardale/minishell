/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 14:33:34 by cdai              #+#    #+#             */
/*   Updated: 2020/05/25 14:39:04 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strsort(char **strs)
{
	char	*temp;
	int		i;

	i = -1;
	while (strs[++i] && strs[i + 1])
	{
		if (ft_strcmp(strs[i], strs[i + 1]) > 0)
		{
			temp = strs[i];
			strs[i] = strs[i + 1];
			strs[i + 1] = temp;
			i = -1;
		}
	}
}
