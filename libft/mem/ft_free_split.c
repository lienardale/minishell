/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 17:51:21 by cdai              #+#    #+#             */
/*   Updated: 2020/09/21 09:59:56 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_free_split(char **data)
{
	int	i;

	i = 0;
	if (data)
		while (data[i])
		{
			free(data[i]);
			data[i] = 0;
			i++;
		}
	free(data);
	return (NULL);
}
