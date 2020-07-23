/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:04:54 by alienard          #+#    #+#             */
/*   Updated: 2020/07/23 13:03:26 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen_gnl(const char *str)
{
	size_t i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup_free_gnl(char *s1)
{
	char	*tab;
	size_t	i;

	i = 0;
	if (!(tab = (char *)malloc(sizeof(char) * (ft_strlen_gnl(s1) + 1))))
		return (NULL);
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	tab[i] = '\0';
	free(s1);
	return (tab);
}

char	*ft_strdup_buff(char *buffer, int ret)
{
	char	*tab;
	int		i;

	if (!(tab = (char *)malloc(sizeof(char) * (ret + 1))))
		return (NULL);
	i = 0;
	while (i != ret)
	{
		tab[i] = buffer[i];
		i++;
	}
	tab[ret] = '\0';
	return (tab);
}

char	*ft_strjoin_free_gnl(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*tab;
	size_t	len;

	if (s2 == NULL)
		return (NULL);
	if (s1 == NULL && (tab = ft_strdup_free_gnl(s2)))
		return (tab);
	len = ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
	if (!(tab = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = -1;
	while (s1[++i])
		tab[i] = s1[i];
	j = -1;
	while (s2[++j])
		tab[i + j] = s2[j];
	tab[i + j] = '\0';
	free(s2);
	free(s1);
	return (tab);
}

int		ft_error(char **line)
{
	char	*tmp;

	tmp = *line;
	if (!(tmp = (char *)malloc(sizeof(char) * 1)))
		return (-1);
	tmp[0] = '\0';
	*line = tmp;
	return (-1);
}
