/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:13:24 by alienard          #+#    #+#             */
/*   Updated: 2020/05/06 13:48:05 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

char	**ft_split_line(char *line)
{
	char	**tokens;
	int		len;
	int		i;

	len = -1;
	i = 0;
	// tokens = ft_split_charset(line, SPACE);
	if (!(tokens = ft_calloc(3, sizeof(char *))))
		return (NULL);
	while (line[++len])
	{
		if (ft_isspace(line[len]))
			break ;
	}
	line[len] = '\0';
	tokens[i++] = ft_strdup(line);
	if (line[++len])
		tokens[i++] = ft_strdup(&line[len]);
	tokens[i] = 0;
	if (!tokens)
	{
		ft_dprintf(2, "minishell: allocation error\n");
		exit(EXIT_FAILURE);
	}
	return (tokens);
}
