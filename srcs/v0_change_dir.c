/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_change_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:10:39 by cdai              #+#    #+#             */
/*   Updated: 2020/08/19 15:34:02 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int	ft_change_dir(t_cmd *cmd, t_sh *sh)
{
	int		chdir_value;
	t_list	*home;

	chdir_value = -1;
// faire . et .. ?
	if (!cmd->av[1] || (!ft_strcmp(cmd->av[1], "~") && !cmd->av[2]))
	{
		home = ft_search_env(*(sh->env), "HOME");
// if (home)
		chdir_value = chdir(((t_env*)home->content)->value);
	}
	else if (cmd->av[1] && cmd->av[2])
		chdir_value = -2;
	else
		chdir_value = chdir(cmd->av[1]);
//	(void)env;
// change pwd et oldpwd dans env
	if (chdir_value == -2)
	{
		ft_putstr_fd("Too much arguments\n", 0);
		ft_free_split(cmd->av);
		return (1);
	}
	else if (chdir_value)
	{
		ft_dprintf(2, "minisehll: cd: %s: No such file or directory\n", cmd->av[1]);
		// ft_putstr_fd(cmd->av[1], 2);
		// ft_putstr_fd("No such file or directory: ", 2);
		// ft_putchar_fd('\n', 2);
		ft_free_split(cmd->av);
		return (1);
	}
	ft_free_split(cmd->av);
	return (1);
}
