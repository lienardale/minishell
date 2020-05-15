/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:13:24 by alienard          #+#    #+#             */
/*   Updated: 2020/05/15 14:18:10 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

size_t	ft_double_strlen(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**ft_split_line(char **inputs)
{
	char	**tokens;
	char	*tmp;
	int		len;
	int		i;

	len = -1;
	i = 1;
	tmp = inputs[0];
	if (inputs && ft_double_strlen(inputs) > 1)
	{
		while (inputs[i])
		{
			tmp = ft_strjoin(tmp, inputs[i]);
			i++;
		}
	}
	tokens = ft_split_quote(tmp, ';');
	// tokens = ft_split_quote(tmp, '|');
	// if (!(tokens = ft_calloc(3, sizeof(char *))))
	// 	return (NULL);
	// while (line[++len])
	// {
	// 	if (ft_isspace(line[len]))
	// 		break ;
	// }
	// line[len] = '\0';
	// tokens[i++] = ft_strdup(line);
	// if (line[++len])
	// 	tokens[i++] = ft_strdup(&line[len]);
	// tokens[i] = 0;
	if (!tokens)
	{
		ft_dprintf(2, "minishell: allocation error\n");
		exit(EXIT_FAILURE);
	}
	return (tokens);
}
