/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 18:51:26 by alienard          #+#    #+#             */
/*   Updated: 2020/05/18 11:16:04 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tab;
	size_t	len;
	size_t	i;
	size_t	j;

	// if (s1 == NULL || s2 == NULL)
	// 	return (NULL);
	if (s2 == NULL)
		return (NULL);
	if (s1 == NULL && (tab = ft_strdup(s2)))
		return (tab);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(tab = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		tab[i + j] = s2[j];
		j++;
	}
	tab[i + j] = '\0';
	return (tab);
}
