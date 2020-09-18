/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:46:53 by cdai              #+#    #+#             */
/*   Updated: 2020/09/18 14:09:30 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ret_nul(void)
{
	char	**tab;

	if (!(tab = (char **)ft_calloc(1, sizeof(char*))))
		return (NULL);
	return (tab);
}

char		*ft_split_quote_concat(char *result, char *str, int start, int i)
{
	char	*temp;
	char	*temp2;

	if (!result)
		result = ft_substr(str, start, i - start);
	else
	{
		temp2 = ft_substr(str, start, i - start);
		temp = ft_strjoin(result, temp2);
		free(temp2);
		free(result);
		result = temp;
	}
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
		while (str[i] && str[i] == c)
			i++;
		start = i;
		if (str[i])
		{
			to_free = ft_split_handle_quote(str, c, start, &i);
			free(to_free);
			nb_word++;
		}
	}
	return (nb_word);
}

char		**ft_split_quote(char *str, char c)
{
	char	**result;
	int		i;
	int		start;
	int		nb_word;

	if (!str || str[0] == 0)
		return (ret_nul());
	i = 0;
	nb_word = 0;
	if (!(result = (char **)ft_calloc((ft_count_word_quote(str, c) + 1),
		sizeof(char*))))
		return (NULL);
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		start = i;
		if (str[i])
		{
			result[nb_word] = ft_split_handle_quote(str, c, start, &i);
			nb_word++;
		}
	}
	return (result);
}
