/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 11:39:31 by cdai              #+#    #+#             */
/*   Updated: 2020/09/02 17:21:02 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_getcwd_increment(char *str, int size)
{
	if (size < 0)
		return (NULL);
	else
	{
		if (!str)
		{
			if (!(str = ft_calloc(1, size)))
				return (NULL);
		}
		else
		{
			free(str);
			if (!(str = ft_calloc(1, size)))
				return (NULL);
		}
	}
	if (getcwd(str, size))
		return (str);
	return (ft_getcwd_increment(str, size * 10));
}

char		*ft_getcwd(void)
{
	char	*working_var;
	char	*result;
	int		size;

	size = 2;
	working_var = NULL;
	if (!(working_var = ft_getcwd_increment(working_var, size)))
		return (NULL);
	else if (!(result = ft_strdup(working_var)))
	{
		free(working_var);
		return (NULL);
	}
	free(working_var);
	return (result);
}
