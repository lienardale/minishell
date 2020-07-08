/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 16:46:29 by alienard          #+#    #+#             */
/*   Updated: 2020/07/08 18:51:40 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

// char	*ft_duptrim_dquotes(char *line)
// {
// 	// char	*new;
// 	size_t	len;

// 	len = 1;
// 	if (ft_isescaped(line))
// 		return (line);
// 	while (line[len] && (line[len] != '\"' || ft_isescaped(&line[len])))
// 		len++;
// 	if (line[len])
// 		return (ft_substr(line, 1, len - 1));
// 	return (line);
// 	// new = ft_strtrim(line, "\"");
// }

// char	*ft_duptrim_squotes(char *line)
// {
	
// }

// char		*ft_trimquotes(char *line)
// {
// 	char	*new;

// 	new = ft_strdup_trim(line, "\"");
// 	new = ft_duptrim_squotes
// 	return (new);
// }

// char		*ft_trimquotes(char *line)
// {
// 	int	nbquote;
// 	int	quote;
// 	int	i;
// 	int	j;

// 	nbquote = 0;
// 	quote = 0;
// 	i = -1;
// 	j = -1;
// 	while (line[++i])
// 	{
// 		if (!quote && ft_ischarset(QUOTE, line[i]) && !ft_isescaped(&line[i]))
// 		{
// 			nbquote++;
// 			quote = line[i];
// 		}
// 		i++;
// 		if (line[i] == quote && !ft_isescaped(&line[i]))
// 		{
// 			nbquote++;
// 			quote = 0;
// 		}
// 	}
// }

int			ft_isindquotes(char *line, int pos)
{
	int	nbquote;
	int	quote;
	int	i;
	int	j;

	nbquote = 0;
	quote = 0;
	i = -1;
	j = -1;
	while (line[++i])
	{
		if (line[i] == '\"' && (quote == '\"' || quote == 0)
			&& !ft_isescaped(&line[i]) && (quote = '\"'))
			nbquote++;
		quote = (nbquote % 2 == 0) ? 0 : quote;
		if (quote != 0 && i < pos)
		{
			j = i;
			while (line[j++])
			{
				if (line[j] == '\"' && quote == '\"'
					&& !ft_isescaped(&line[j]))
					nbquote++;
				if (nbquote % 2 == 0 && j > pos)
					return (1);
				if (nbquote % 2 == 0 && (nbquote = 0))
					break ;
			}
		}
	}
	return (0);
}

int			ft_isinsquotes(char *line, int pos)
{
	int	nbquote;
	int	quote;
	int	i;
	int	j;

	nbquote = 0;
	quote = 0;
	i = -1;
	j = -1;
	while (line[++i])
	{
		if (line[i] == '\'' && (quote == '\'' || quote == 0)
			&& !ft_isescaped(&line[i]) && (quote = '\''))
			nbquote++;
		quote = (nbquote % 2 == 0) ? 0 : quote;
		if (quote != 0 && i < pos)
		{
			j = i;
			while (line[j++])
			{
				if (line[j] == '\'' && quote == '\''
					&& !ft_isescaped(&line[j]))
					nbquote++;
				if (nbquote % 2 == 0 && j > pos)
					return (1);
				if (nbquote % 2 == 0 && (nbquote = 0))
					break ;
			}
		}
	}
	return (0);
}

int			ft_isinquotes(char *line, int pos)
{
	int	nbquote;
	int	quote;
	int	i;
	int	j;

	nbquote = 0;
	quote = 0;
	i = -1;
	j = -1;
	while (line[++i])
	{
		if (line[i] == '\'' && (quote == '\'' || quote == 0)
			&& !ft_isescaped(&line[i]) && (quote = '\''))
			nbquote++;
		if (line[i] == '\"' && (quote == '\"' || quote == 0)
			&& !ft_isescaped(&line[i]) && (quote = '\"'))
			nbquote++;
		quote = (nbquote % 2 == 0) ? 0 : quote;
		if (quote != 0 && i < pos)
		{
			j = i;
			while (line[j++])
			{
				if (line[j] == '\'' && quote == '\''
					&& !ft_isescaped(&line[j]))
					nbquote++;
				if (line[j] == '\"' && quote == '\"'
					&& !ft_isescaped(&line[j]))
					nbquote++;
				if (nbquote % 2 == 0 && j > pos)
					return (1);
				if (nbquote % 2 == 0 && (nbquote = 0))
					break ;
			}
		}
	}
	return (0);
}

