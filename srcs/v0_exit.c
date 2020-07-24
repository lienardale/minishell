/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 14:40:49 by alienard          #+#    #+#             */
/*   Updated: 2020/07/24 15:09:33 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int		ft_exit(t_cmd *cmd, t_sh *sh)
{
	// ft_printf("			-> %s passe bien par ici.\n", cmd->av[0]);
	ft_free_double_array(cmd->av);
	ft_lstclear(sh->env, ft_free_env_lst);
	exit(1);
	return (0);
}
