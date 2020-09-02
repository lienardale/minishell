/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_clean.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 10:32:33 by alienard          #+#    #+#             */
/*   Updated: 2020/09/02 14:00:26 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

// static size_t	ft_strlen_dol(char *str, size_t i, size_t *len)
// {
// 	if (ft_is_escaped(str, i) || ft_isinsquotes(str, i)
// 		|| !str[i + 1] || ft_isspace(str[i + 1]) || str[i + 1] == '\\'
// 		|| (ft_isindquotes(str, i) && !ft_isalnum(str[i + 1])))
// 		(*len)++;
// 	i = str[i] == '$' ? i + 1 : i;
// 	if (str[i] && ft_isalnum(str[i]) && !ft_isinsquotes(str, i)
// 		&& !ft_is_escaped(str, i - 1))
// 	{
// 		if (ft_isdigit(str[i]))
// 			return (i);
// 		while (ft_isalnum(str[i]))
// 			i++;
// 		i--;
// 		return (i);
// 	}
// 	i--;
// 	return (i);
// }

// static void		ft_strcpy_dol(char *dst, char *src, size_t *i, size_t *j)
// {
// 	if (ft_is_escaped(src, *i) || ft_isinsquotes(src, *i)
// 		|| !src[*i + 1] || ft_isspace(src[*i + 1]) || src[*i + 1] == '\\'
// 		|| (ft_isindquotes(src, *i) && !ft_isalnum(src[*i + 1])))
// 	{
// 		dst[*j] = src[*i];
// 		(*j)++;
// 	}
// 	*i = src[*i] == '$' ? *i + 1 : *i;
// 	if (src[*i] && ft_isalnum(src[*i]) && !ft_isinsquotes(src, *i)
// 		&& !ft_is_escaped(src, *i - 1))
// 	{
// 		if (ft_isdigit(src[*i]))
// 			return ;
// 		while (ft_isalnum(src[*i]))
// 			(*i)++;
// 		(*i)--;
// 		return ;
// 	}
// 	(*i)--;
// }

static size_t	ft_strlen_clean(char *str)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != '\\' && str[i] != '\"' && str[i] != '\'' /*&& str[i] != '$'*/)
			len++;
		else if (str[i] == '\\' && (ft_isinsquotes(str, i)
			|| (ft_isindquotes(str, i) && str[i + 1] != '\"'
			&& str[i + 1] != '$' && str[i + 1] != '\\')
			|| ft_is_escaped(str, i)))
			len++;
		else if (str[i] == '\"' && (ft_isinsquotes(str, i)
			|| ft_is_escaped(str, i)))
			len++;
		else if (str[i] == '\'' && (ft_isindquotes(str, i)
			|| (ft_is_escaped(str, i) && !ft_isinsquotes(str, i - 1))))
			len++;
		// else if (str[i] == '$')
			// i = ft_strlen_dol(str, i, &len);
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
	while (dstsize > 0 && src[++i] && (j < (dstsize - 1)))
	{
		if (src[i] != '\\' && src[i] != '\"' && src[i] != '\''/* && src[i] != '$'*/
			&& (dst[j] = src[i]))
			j++;
		else if (src[i] == '\\' && ((ft_isinsquotes(src, i))
			|| (ft_isindquotes(src, i) && src[i + 1] != '\"'
			&& src[i + 1] != '$' && src[i + 1] != '\\')
			|| ft_is_escaped(src, i)) && (dst[j] = src[i]))
			j++;
		else if (src[i] == '\"' && (ft_isinsquotes(src, i)
			|| ft_is_escaped(src, i)) && (dst[j] = src[i]))
			j++;
		else if (src[i] == '\'' && (ft_isindquotes(src, i)
			|| (ft_is_escaped(src, i) && !ft_isinsquotes(src, i - 1)))
			&& (dst[j] = src[i]))
			j++;
		// else if (src[i] == '$')
			// ft_strcpy_dol(dst, src, &i, &j);
	}
	dst[j] = '\0';
}

char			*ft_strdup_clean(const char *s1)
{
	char	*us1;
	char	*tab;

	us1 = (char *)s1;
	// printf("str:%s\n", us1);
	if (!(tab = (char *)malloc(sizeof(char) * (ft_strlen_clean(us1) + 1))))
		return (NULL);
	ft_strlcpy_clean(tab, us1, ft_strlen_clean(us1) + 1);
	return (tab);
}
