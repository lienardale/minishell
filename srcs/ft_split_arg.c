/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 11:04:50 by alienard          #+#    #+#             */
/*   Updated: 2020/07/08 15:20:45 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

static char	**ret_nul(void)
{
	char	**tab;

	if (!(tab = (char **)ft_calloc(1, sizeof(char*))))
		return (NULL);
	return (tab);
}

static char	*ft_split_quote_concat(char *result, char *str, int start, int i)
{
	char	*temp;
	char	*temp2;

	if (!result)
		result = ft_substr(str, start, i - start);
	else
	{
		temp2 = ft_substr(str, start, i - start);
		temp = ft_strjoin(result, temp2);
		free(result);
		free(temp2);
		result = temp;
	}
	return (result);
}

static char	*ft_handle_quote(char *str, char c, int start, int *i)
{
	char	*result;
	char	quote;

	result = NULL;
	quote = (str[start] == '\'' || str[start] == '\"') ? str[start] : 0;
	// start = quote ? start + 1 : start;
	*i = quote ? *i + 1 : *i;
	while (str[*i] && ((!quote && str[*i] != c) || (quote)))
	{
		if (str[*i] == quote && !ft_isescaped(&str[*i]))
		{
			result = ft_split_quote_concat(result, str, start, *i);
			quote = 0;
			// start = *i + 1;
			start = *i;
		}
		(*i)++;
		if (!quote && (str[*i] == '\'' || str[*i] == '\"') && !ft_isescaped(&str[*i]))
		{
			result = ft_split_quote_concat(result, str, start, *i);
			quote = str[*i];
			// (*i)++;
			start = *i;
		}
	}
	// result = (!(str[*i - 1] == '\'' || str[*i - 1] == '\"')) ?
		// ft_split_quote_concat(result, str, start, *i) : result;
	result = (!(str[*i] == '\'' || str[*i] == '\"')) ?
		ft_split_quote_concat(result, str, start, *i) : result;
	// printf("*i:%d\n", *i);
	return (result);
}

static int	ft_count_word_quote(char *str, char c)
{
	char	*to_free;
	int		i;
	int		start;
	int		nb_word;

	i = 0;
	nb_word = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c && !ft_isescaped(&str[i]))
			i++;
		start = i;
		if (str[i])
		{
			to_free = ft_handle_quote(str, c, start, &i);
			free(to_free);
			nb_word++;
		}
	}
	return (nb_word);
}

char		**ft_split_arg(char *str)
{
	char	**result;
	int		i;
	int		start;
	int		nb_word;

	if (!str || str[0] == 0)
		return (ret_nul());
	i = 0;
	nb_word = 0;
	if (!(result = (char **)ft_calloc((ft_count_word_quote(str, ' ') + 1),
		sizeof(char*))))
		return (NULL);
	while (str[i])
	{
		while (str[i] && str[i] == ' ' && !ft_isescaped(&str[i]))
			i++;
		start = i;
		if (str[i])
		{
			result[nb_word] = ft_handle_quote(str, ' ', start, &i);
			nb_word++;
		}
	}
	return (result);
}
