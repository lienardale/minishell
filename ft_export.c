/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 07:54:41 by cdai              #+#    #+#             */
/*   Updated: 2020/05/14 08:36:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int	ft_export(char **args, char **env)
{
	int	i;

	i = 0;
	if (!args[1])
		while (env[i])
		{
			ft_putendl_fd(env[i], 0);
			i++;
		}
	else
	{
		while (args[1][i])
		{
			if (args[1][i] == '=')
				ft_splitadd_back(env, args[1]);
			i++;
		}
	}
	return (1);
}
