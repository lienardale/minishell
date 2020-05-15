/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 12:46:53 by cdai              #+#    #+#             */
/*   Updated: 2020/05/15 15:12:08 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

static char	**ret_nul(void)
{
	char **tab;

	if (!(tab = (char **)malloc(sizeof(char*) * 1)))
		return (NULL);
	tab[0] = 0;
	return (tab);
}

static int	ft_count_word_quote(char *str, char c)
{
	char quote;
	int nb_word;
	int i;

	quote = 0;
	i = 0;
	nb_word = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c && !quote)
			i++;
		while (str[i] && (str[i] != c || quote))
		{
			if (!quote && (str[i] == '\'' || str[i] == '\"'))
				quote = str[i];
			else if (quote && str[i] == quote)
				quote = 0;
			i++;
		}
		nb_word++;
	}
	return (nb_word);
}

char		**ft_split_quote(char *str, char c)
{
	char **result;
	char quote;
	int nb_word;
	int i;
	int start;

	if (!str || str[0] == 0)
		return (ret_nul());
	quote = 0;
	i = 0;
	nb_word = ft_count_word_quote(str, c);
	if (!(result = (char **)malloc(sizeof(char*) * (nb_word + 1))))
		return (NULL);
	nb_word = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c && !quote)
			i++;
		start = i;
		while (str[i] && (str[i] != c || quote))
		{
			if (!quote && (str[i] == '\'' || str[i] == '\"'))
				quote = str[i];
			else if (quote && str[i] == quote)
				quote = 0;
			i++;
		}
		result[nb_word] = ft_substr(str, start, i - start);
		nb_word++;
	}
	result[nb_word] = 0;
	return result;
}
