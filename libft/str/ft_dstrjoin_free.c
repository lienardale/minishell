/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstrjoin_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 10:16:29 by alienard          #+#    #+#             */
/*   Updated: 2020/07/23 13:06:22 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			**ft_dstrjoin_free(char **s1, char **s2)
{
	char	**tab;
	size_t	len;
	size_t	i;
	size_t	j;

	if (s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_dstrdup_free(s2));
	len = ft_double_strlen(s1) + ft_double_strlen(s2);
	if (!(tab = (char **)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	i = -1;
	while (s1[++i])
		tab[i] = ft_strdup_free(s1[i]);
	j = -1;
	while (s2[++j])
		tab[i + j] = ft_strdup_free(s2[j]);
	tab[i + j] = 0;
	ft_free_double_array(s1);
	ft_free_double_array(s2);
	return (tab);
}

char			**ft_dstrjoin(char **s1, char **s2)
{
	char	**tab;
	size_t	len;
	size_t	i;
	size_t	j;

	if (s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_dstrdup(s2));
	len = ft_double_strlen(s1) + ft_double_strlen(s2);
	if (!(tab = (char **)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	i = -1;
	while (s1[++i])
		tab[i] = ft_strdup(s1[i]);
	j = -1;
	while (s2[++j])
		tab[i + j] = ft_strdup(s2[j]);
	tab[i + j] = 0;
	return (tab);
}
