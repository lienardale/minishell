/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 09:31:04 by cdai              #+#    #+#             */
/*   Updated: 2020/09/23 17:16:44 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*ft_parse_path(char **path)
{
	int		start;
	int		i;
	char	*result;

	start = ft_strlen(*path);
	i = start - 1;
	while (i > -1 && (*path)[i] != '/')
		i--;
	if (!(result = ft_strdup(*path)))
		return (NULL);
	if (!(*path = ft_substr(*path, i + 1, start - i)))
		return (NULL);
	return (result);
}
