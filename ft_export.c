/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 07:54:41 by cdai              #+#    #+#             */
/*   Updated: 2020/05/25 14:32:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int	ft_export(char **args, char **env)
{
	int		i;
	char	**temp;

	i = 0;
	temp = 0;
	if (!args[1])
	{
		temp = ft_splitcpy(env);
		ft_strsort(temp);
		while (temp[i])
		{
//remettre les path dans l'ordre avant de les print
//ne pas oublier de ne print que les clef avec valeur (voir signe '=')
			ft_putendl_fd(temp[i], 0);
			i++;
		}
		ft_free_split(temp);
	}
	else
	{
//attention, ce n'est pas le comportement souhaité
		while (args[1][i])
		{
			if (args[1][i] == '=')
				ft_splitadd_back(env, args[1]);
			i++;
		}
	}
ft_free_split(args);
	return (1);
}
