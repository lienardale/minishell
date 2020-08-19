/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 16:46:29 by alienard          #+#    #+#             */
/*   Updated: 2020/08/17 18:21:46 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

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
			&& !ft_is_escaped(line, i) && (quote = '\"'))
			nbquote++;
		quote = (nbquote % 2 == 0) ? 0 : quote;
		if (quote != 0 && i < pos)
		{
			j = i;
			while (line[j++] && nbquote != 0)
			{
				if (line[j] == '\"' && quote == '\"'
					&& !ft_is_escaped(line, j))
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
			&& !ft_is_escaped(line, i) && (quote = '\''))
			nbquote++;
		quote = (nbquote % 2 == 0) ? 0 : quote;
		if (quote != 0 && i < pos)
		{
			j = i;
			while (line[j++] && nbquote != 0)
			{
				if (line[j] == '\'' && quote == '\''
					/*&& !ft_is_escaped(line, j)*/)
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
			&& !ft_is_escaped(line, i) && (quote = '\''))
			nbquote++;
		if (line[i] == '\"' && (quote == '\"' || quote == 0)
			&& !ft_is_escaped(line, i) && (quote = '\"'))
			nbquote++;
		quote = (nbquote % 2 == 0) ? 0 : quote;
		if (quote != 0 && i < pos)
		{
			j = i;
			while (line[++j] && nbquote != 0)
			{
				if (line[j] == '\'' && quote == '\''
					/*&& !ft_is_escaped(line, j)*/)
					nbquote++;
				if (line[j] == '\"' && quote == '\"'
					&& !ft_is_escaped(line, j))
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

