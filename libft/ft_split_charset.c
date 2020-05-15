/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 10:03:19 by alienard          #+#    #+#             */
/*   Updated: 2020/05/15 15:00:43 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char	**ft_free_all(char **ret, char *tmp)
{
	int	i;

	i = 0;
	ft_free_ptr(tmp);
	while (ret[i])
	{
		ft_free_ptr(ret[i]);
		i++;
	}
	return (NULL);
}

static char	**ret_nul(void)
{
	char **tab;

	if (!(tab = (char **)malloc(sizeof(char*) * 1)))
		return (NULL);
	tab[0] = 0;
	return (tab);
}

static int	ft_init(char **tmp, const char *set)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while ((*tmp)[i])
	{
		j = 0;
		while (set[j])
		{
			if ((*tmp)[i] == set[j])
			{
				(*tmp)[i] = '\0';
				if (i != 0 && (*tmp)[i - 1])
					k++;
			}
			j++;
		}
		i++;
	}
	if ((*tmp)[i - 1])
		k++;
	return (k);
}

static char	**ft_fill(int len, char *s, char *tmp, char **ret)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (i < len)
	{
		while (s[i] == '\0' && i < len)
			i++;
		if (s[i])
		{
			if (!(ret[j] = (char*)malloc(sizeof(char) *
					(ft_strlen(&s[i]) + 1))))
				return (ft_free_all(ret, tmp));
			ret[j][ft_strlen(&s[i])] = '\0';
			k = 0;
			while (s[i])
				ret[j][k++] = s[i++];
			j++;
		}
	}
	ft_free_ptr(tmp);
	return (ret);
}

char		**ft_split_charset(const char *s, const char *set)
{
	char	*tmp;
	char	*tmp_2;
	char	**ret;
	int		len;
	int		i;

	if (!s || !set || s[0] == 0 || !(tmp = ft_strdup(s)))
		return (ret_nul());
	len = ft_strlen(s);
	i = ft_init(&tmp, set);
	if (!(ret = (char **)malloc(sizeof(char *) * (i + 1))))
	{
		ft_free_ptr(tmp);
		return (NULL);
	}
	ret[i] = NULL;
	tmp_2 = tmp;
	return (ft_fill(len, tmp, tmp_2, ret));
}
