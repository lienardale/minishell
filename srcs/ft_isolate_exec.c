/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isolate_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:16:11 by cdai              #+#    #+#             */
/*   Updated: 2020/09/23 16:43:02 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isolate_exec(char *path, char **buff)
{
	int		path_len;
	int		i;

	path_len = ft_strlen(path);
	i = path_len - 1;
	while (i > -1 && path[i] != '/')
		i--;
	if (i > -1 && path[i] == '/')
	{
		if (!(*buff = ft_substr(path, i + 1, path_len - i)))
			return (-1);
	}
	return (i);
}
