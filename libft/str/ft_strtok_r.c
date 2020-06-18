/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 12:15:56 by alienard          #+#    #+#             */
/*   Updated: 2020/04/15 12:47:21 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strspn(char *s, const char *delim)
{
	int	i;
	int	j;
	int in;

	i = 0;
	while (s[i])
	{
		in = 1;
		j = 0;
		while (delim[j])
		{
			if (s[i] == delim[j])
				in = 0;
			j++;
		}
		if (in)
			return (i);
		i++;
	}
	return (i);
}

static int	ft_strcspn(char *s, const char *delim)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (delim[j])
		{
			if (s[i] == delim[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

char		*ft_strtok_r(char *s, const char *delim, char **save_ptr)
{
	char *end;

	if (s == NULL)
		s = *save_ptr;
	if (*s == '\0')
	{
		*save_ptr = s;
		return (NULL);
	}
	s += ft_strspn(s, delim);
	if (*s == '\0')
	{
		*save_ptr = s;
		return (NULL);
	}
	end = s + ft_strcspn(s, delim);
	if (*end == '\0')
	{
		*save_ptr = end;
		return (s);
	}
	*end = '\0';
	*save_ptr = end + 1;
	return (s);
}
