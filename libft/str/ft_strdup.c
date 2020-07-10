/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 20:37:03 by alienard          #+#    #+#             */
/*   Updated: 2020/07/10 11:14:10 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*us1;
	char	*tab;

	us1 = (char *)s1;
	if (!(tab = (char *)malloc(sizeof(char) * (ft_strlen(us1) + 1))))
		return (NULL);
	ft_strlcpy(tab, us1, ft_strlen(us1) + 1);
	return (tab);
}
