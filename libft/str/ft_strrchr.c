/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:09:15 by alienard          #+#    #+#             */
/*   Updated: 2020/06/22 14:10:19 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*us;
	size_t	len;

	us = (char *)s;
	len = ft_strlen(us);
	while (len != 0 && us[len] != c)
		len--;
	if (us[len] != c)
		return (NULL);
	return (&us[len]);
}
