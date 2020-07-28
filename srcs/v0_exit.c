/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 14:40:49 by alienard          #+#    #+#             */
/*   Updated: 2020/08/05 12:40:01 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int		ft_exit(t_cmd *cmd, t_sh *sh)
{
	int	i;

	i = 0;
	while (cmd->av[i])
		i++;
	// ft_printf("			-> %s passe bien par ici.\n", args[0]);
	ft_free_double_array(cmd->av);
	ft_lstclear(sh->env, ft_free_env_lst);
/*
	if (i > 2)
	{
		ft_printf("minishell: exit: too many arguments\n");
		return (1);
	}
	else if (i == 2)
	{
		if (ft_is_double_minus(args[1]))
			exit(sh->cmds_val);
		if (ft_str_isdigit(args[1]) && ft_is_in_min_max_atoi_long(args[1]))
		{
// over int max
			return_value = ft_atoi_long(args[1]) % 256;
			if (return_value < 0)
				exit(return_value + 256);
			else
				exit(return_value);
		}
		else
		{
			ft_printf(minishell: exit: %s: numeric argument required\n);
			exit(255);
		}
	}
	else
	{
		exit(sh->cmds_val);
	}
*/
	return (0);
}
