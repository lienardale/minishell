/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_handle_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 14:01:13 by alienard          #+#    #+#             */
/*   Updated: 2020/09/18 14:10:08 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_isquote(char *quote, char **str, int *start, int *i)
{
	*quote = (*str)[*i];
	if (ft_is_escaped(*str, *i) && (*str)[*i] != ' ')
		*quote = 0;
	if (ft_is_escaped(*str, *i) && (*str)[*i] == ' ')
		*quote = ' ';
	*start = *i;
	if ((*quote == '\'' || *quote == '\"') && (*str)[*i + 1]
		&& ft_isinquotes(*str, *i + 1))
		*i = *i + 1;
}

char		*ft_split_handle_quote(char *str, char c, int start, int *i)
{
	char	*result;
	char	quote;

	result = NULL;
	quote = (str[start] == '\'' || str[start] == '\"') ? str[start] : 0;
	*i = (quote) ? *i + 1 : *i;
	while (str[*i] && ((!quote && str[*i] != c) || (quote)))
	{
		if (str[*i] == quote && (!ft_is_escaped(str, *i) || quote == ' '))
		{
			result = ft_split_quote_concat(result, str, start, *i);
			quote = 0;
			start = *i;
		}
		(*i)++;
		if ((!quote && (str[*i] == '\'' || str[*i] == '\"'))
			|| ft_is_escaped(str, *i))
		{
			result = ft_split_quote_concat(result, str, start, *i);
			ft_isquote(&quote, &str, &start, i);
		}
	}
	result = (!(str[*i] == '\'' || str[*i] == '\"')) ?
		ft_split_quote_concat(result, str, start, *i) : result;
	return (result);
}
