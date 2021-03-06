/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 16:46:29 by alienard          #+#    #+#             */
/*   Updated: 2020/09/18 13:01:25 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_ifquote(t_quote *is, char *line, int pos)
{
	is->j = is->i;
	while (line[++is->j] && is->nbquote != 0)
	{
		if (line[is->j] == '\'' && is->quote == '\'')
			is->nbquote++;
		if (line[is->j] == '\"' && is->quote == '\"'
			&& !ft_is_escaped(line, is->j))
			is->nbquote++;
		if (is->nbquote % 2 == 0 && is->j > pos)
			return (1);
		if (is->nbquote % 2 == 0)
		{
			is->nbquote = 0;
			is->quote = 0;
			is->i = is->j;
			break ;
		}
	}
	return (0);
}

int			ft_isinquotes(char *line, int pos)
{
	t_quote	is;

	is.nbquote = 0;
	is.quote = 0;
	is.i = -1;
	is.j = -1;
	while (line[++is.i])
	{
		if (line[is.i] == '\'' && (is.quote == '\'' || is.quote == 0)
			&& !ft_is_escaped(line, is.i) && (is.quote = '\''))
			is.nbquote++;
		if (line[is.i] == '\"' && (is.quote == '\"' || is.quote == 0)
			&& !ft_is_escaped(line, is.i) && (is.quote = '\"'))
			is.nbquote++;
		is.quote = (is.nbquote % 2 == 0) ? 0 : is.quote;
		if (is.quote != 0 && is.i < pos)
		{
			if (ft_ifquote(&is, line, pos))
				return (1);
		}
	}
	return (0);
}
