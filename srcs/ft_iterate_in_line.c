/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterate_in_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 10:37:31 by alienard          #+#    #+#             */
/*   Updated: 2020/09/18 10:42:27 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_iterate_in_line(char *line, int *j, char *set)
{
	while (line[*j])
	{
		if (ft_ischarset(set, line[*j]) && !ft_isinquotes(line, *j)
			&& !ft_is_escaped(line, *j))
			break ;
		(*j)++;
	}
	return (1);
}

int		ft_iterate_in_line_redir(char *line, int *j, char *set)
{
	while (line[*j] && (!ft_isspace(line[*j]) || ft_is_escaped(line, *j)))
	{
		if (ft_ischarset(set, line[*j]) && !ft_isinquotes(line, *j)
			&& !ft_is_escaped(line, *j))
			break ;
		(*j)++;
	}
	return (1);
}

int		ft_iterate_in_line_space(char *line, int *i)
{
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	return (1);
}

int		ft_iterate_in_line_space_esc(char *line, int *j)
{
	while (line[*j] && ft_isspace(line[*j]) && !ft_is_escaped(line, *j))
		(*j)++;
	return (1);
}
