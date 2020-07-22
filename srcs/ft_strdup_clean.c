/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_clean.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 10:32:33 by alienard          #+#    #+#             */
/*   Updated: 2020/07/22 16:11:52 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int		ft_is_escaped(char *str, int pos)
{
	int	i;
	int	bkslh;

	i = 0;
	bkslh = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			bkslh++;
		if (i == pos)
			return ((bkslh % 2 == 0) ? 0 : 1);
		i++;
	}
	return ((bkslh % 2 == 0) ? 0 : 1);
}

static size_t	ft_strlen_clean(char *str)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != '\\' && str[i] != '\"' && str[i] != '\'')
			len++;
		else if (str[i] == '\\' && (ft_isinsquotes(str, i)
			|| (ft_isindquotes(str, i) && str[i + 1] != '\"')
			|| (ft_isescaped(&str[i]) && !ft_isescaped(&str[i - 1]))))
			len++;
		else if (str[i] == '\"' && (ft_isinsquotes(str, i)
			|| ft_isescaped(&str[i])))
			len++;
		else if (str[i] == '\'' && (ft_isindquotes(str, i)
			|| (ft_isescaped(&str[i]) && !ft_isinsquotes(str, i - 1))))
			len++;
		i++;
	}
	return (len);
}

static void		ft_strlcpy_clean(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;

	if (dstsize <= 0)
		return ;
	while (src[++i] && (j < (dstsize - 1)))
	{
		if (src[i] != '\\' && src[i] != '\"' && src[i] != '\''
			&& (dst[j] = src[i]))
			j++;
		else if (src[i] == '\\' && ((ft_isinsquotes(src, i))
			|| (ft_isindquotes(src, i) && src[i + 1] != '\"')
			|| (ft_isescaped(&src[i]) && !ft_isescaped(&src[i - 1])))
			&& (dst[j] = src[i]))
			j++;
		else if (src[i] == '\"' && (ft_isinsquotes(src, i)
			|| ft_isescaped(&src[i])) && (dst[j] = src[i]))
			j++;
		else if (src[i] == '\'' && (ft_isindquotes(src, i)
			|| (ft_isescaped(&src[i]) && !ft_isinsquotes(src, i - 1)))
			&& (dst[j] = src[i]))
			j++;
	}
	dst[j] = '\0';
}

char			*ft_strdup_clean(const char *s1)
{
	char	*us1;
	char	*tab;

	us1 = (char *)s1;
	if (!(tab = (char *)malloc(sizeof(char) * (ft_strlen_clean(us1) + 1))))
		return (NULL);
	ft_strlcpy_clean(tab, us1, ft_strlen_clean(us1) + 1);
	return (tab);
}
