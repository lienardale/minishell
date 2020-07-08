/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_escape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 16:47:13 by alienard          #+#    #+#             */
/*   Updated: 2020/07/08 18:37:09 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

void	ft_parse_escape(int *j, char *line, t_cmd *cmd)
{
	int		i;
	char	*beg;
	char	*end;

	i = 0;
	if (ft_isindquotes(line, *j) && line[*j + 1] != '\"')
		return ;
	(void)cmd;
	line[*j] = '\0';
	beg = ft_strdup(line);
	end = ft_strdup(&line[*j + 1]);
	free(line);
	line = ft_strjoin(beg, end);
	free(beg);
	free(end);
}

int		ft_isescaped(char *c)
{
	if (*(c - 1) == '\\')
		return (1);
	return (0);
}
