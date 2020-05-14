/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitadd_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 08:40:02 by cdai              #+#    #+#             */
/*   Updated: 2020/05/14 10:27:31 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_splitadd_back(char **strs, char *str)
{
	int		nb_address;
	int		i;
	char	**result;

	nb_address = 0;
	while (strs[nb_address])
		nb_address++;
	if (!(result = ft_calloc(nb_address + 2, sizeof(char*))))
		return (NULL);
	i = 0;
	while (i < nb_address)
	{
		if (!(result[i] = ft_strdup(strs[i])))
		{
			ft_free_split(result);
			return (NULL);
		}
		i++;
	}
	if (!(result[i] = ft_strdup(str)))
	{
		ft_free_split(result);
		return (NULL);
	}
	return (result);
}
