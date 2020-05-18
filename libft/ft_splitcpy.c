/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitcpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 19:54:17 by cdai              #+#    #+#             */
/*   Updated: 2020/05/17 20:12:46 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_splitcpy(char **src)
{
	int		i;
	char	**result;

	i = 0;
	while (src[i])
		i++;
	if (!(result = ft_calloc(i + 1, sizeof(char*))))
	{
		ft_free_split(result);
		return (NULL);
	}
	i = 0;
	while (src[i])
	{
		if (!(result[i] = ft_strdup(src[i])))
		{
			ft_free_split(result);
			return (NULL);
		}
		i++;
	}
	return (result);
}
