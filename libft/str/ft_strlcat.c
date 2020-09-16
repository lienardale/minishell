/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:48:07 by alienard          #+#    #+#             */
/*   Updated: 2020/09/16 17:45:56 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	lendst;

	i = 0;
	j = 0;
	lendst = ft_strlen(dst);
	while (dst[j])
		j++;
	while (src[i] && j + 1 < dstsize)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	if (j < dstsize)
		dst[j] = '\0';
	if (dstsize < lendst)
		return (ft_strlen(src) + dstsize);
	return (lendst + ft_strlen(src));
}
