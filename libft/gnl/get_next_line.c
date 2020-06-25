/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 20:19:38 by alienard          #+#    #+#             */
/*   Updated: 2020/06/26 00:12:36 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlen_gnl(char *str)
{
	size_t i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
		i++;
	return (i);
}

static char	*ft_strjoin_free(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*tab;
	size_t	len;

	if (s2 == NULL)
		return (NULL);
	if (s1 == NULL && (tab = ft_strdup(s2)))
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
	free(s1);
	s1 = NULL;
	return (tab);
}

static char	*ft_gnlsubstr(char const *s, unsigned int start, size_t len)
{
	char	*tab;
	char	*us;
	size_t	i;

	if (!s || s[0] == '\0' || len == 0)
		return (NULL);
	us = (char *)s;
	i = 0;
	if (!(tab = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len && us[i] && start <= ft_strlen(us))
		tab[i++] = us[start++];
	tab[i] = '\0';
	return (tab);
}

int		get_next_line(int fd, char **line)
{
	char		buffer[301];
	static char	*rest = NULL;
	int		retread;
	char		*n;
	int			i;

	if (!line)
		return (-1);
	while ((retread = read(fd, buffer, 300)) > 0)
	{
		if (!retread)
			break ;
		buffer[retread] = '\0';
		rest = ft_strjoin_free(rest, buffer);
		if ((n = ft_strchr(rest, '\n')))
		{
			n[0] = '\0';
			i = ft_strlen(rest);
			*line = rest;
			rest = ft_gnlsubstr(rest, i + 1, ft_strlen(rest + i + 1));
			return (1);
		}
	}
	// ft_free_ptr(rest);
	return (retread);
}
