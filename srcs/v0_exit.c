/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 14:40:49 by alienard          #+#    #+#             */
/*   Updated: 2020/08/11 12:05:18 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

static int	ft_is_double_minus(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '-')
		i++;
	if (i == 2 && str[i] == 0)
		return (1);
	return (0);
}

int		ft_exit(t_cmd *cmd, t_sh *sh)
{
	int		i;
	int		return_value;

	i = -1;
	while (cmd->av[++i])
		printf("%s\n", cmd->av[i]);
	i = 0;
	if (!cmd)
	{
		return_value = sh->ret_cmd;
		ft_lstclear(sh->env, ft_free_env_lst);
		ft_printf("exit\n");
		exit(return_value);
	}
	while (cmd->av[i])
		i++;
	// ft_printf("			-> %s passe bien par ici.\n", args[0]);
// on devrait peut-etre faire une fontion free_minishell() ?

//	ft_free_double_array(cmd->av);
//	ft_lstclear(sh->env, ft_free_env_lst);
	if (i > 2)
	{
		ft_dprintf(2, "minishell: exit: too many arguments\n");
		exit(1);
	}
	else if (i == 2)
	{
		if (ft_is_double_minus(cmd->av[1]))
		{
			return_value = sh->ret_cmd;
//			ft_free_sh();
			exit(return_value);
		}
		if (ft_str_isdigit(cmd->av[1]) && ft_is_in_min_max_atoi_long(cmd->av[1]))
		{
// over int max
//			ft_free_sh();
			return_value = ft_atoi_long(cmd->av[1]) % 256;
			return_value = (return_value < 0) ? return_value + 256 : return_value;
			exit(return_value);
		}
		else
		{
			ft_dprintf(2, "minishell: exit: %s: numeric argument required\n", cmd->av[1]);
//			ft_free_sh();
			exit(255);
		}
	}
	else
	{
		return_value = sh->ret_cmd;
//		ft_free_sh();
		exit(return_value);
	}
	return (0);
}
