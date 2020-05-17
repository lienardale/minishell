/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:13:24 by alienard          #+#    #+#             */
/*   Updated: 2020/05/15 20:53:16 by alienard         ###   ########.fr       */
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
	if (!tokens)
	{
		ft_dprintf(2, "minishell: allocation error\n");
		exit(EXIT_FAILURE);
	}
	return (tokens);
}
