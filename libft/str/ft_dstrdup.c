/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstrdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:10:45 by alienard          #+#    #+#             */
/*   Updated: 2020/07/23 13:01:45 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dstrdup(char **src)
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

char	**ft_dstrdup_free(char **src)
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
		if (!(result[i] = ft_strdup_free(src[i])))
		{
			ft_free_split(result);
			return (NULL);
		}
		i++;
	}
	ft_free_double_array(src);
	return (result);
}
