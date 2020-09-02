/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_escape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 16:47:13 by alienard          #+#    #+#             */
/*   Updated: 2020/09/02 17:32:16 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int		ft_is_escaped(char *str, int pos)
{
	int	i;
	int	bkslh;

	i = 0;
	bkslh = 0;
	while (str[i])
	{
		if (str[i] != '\\')
			bkslh = 0;
		if (str[i] == '\\')
			bkslh++;
		i++;
		if (i == pos)
			return ((bkslh % 2 == 0) ? 0 : 1);
	}
	return ((bkslh % 2 == 0) ? 0 : 1);
}
