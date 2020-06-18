/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 19:02:58 by alienard          #+#    #+#             */
/*   Updated: 2020/04/14 21:00:03 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	size_t	new_size;
	char	*new_ptr;
	char	*tmp;

	tmp = (char*)ptr;
	if (!ptr)
	{
		if (!(new_ptr = (char *)malloc(sizeof(char) * size)))
			return (NULL);
		return (new_ptr);
	}
	new_size = ft_strlen(tmp);
	if (size <= new_size)
		return (ptr);
	if (!(new_ptr = ft_strdup(ptr)))
		return (NULL);
	free(ptr);
	return (new_ptr);
}
