/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 14:40:49 by alienard          #+#    #+#             */
/*   Updated: 2020/07/24 21:53:20 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int		ft_exit(t_cmd *cmd, t_sh *sh)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	// ft_printf("			-> %s passe bien par ici.\n", args[0]);
	ft_free_double_array(args);
	ft_lstclear(env, ft_free_env_lst);
/*
	if (i == 2)
	{
		return_value = args[1] % 256;
		if (return_value < 0)
			return (return_value + 256);
		else
			return (return_value);
	}
	else (i > 2)
	{
		ft_printf("minishell: exit: too many arguments\n");
		return (1);
	}
*/
	return (0);
}
