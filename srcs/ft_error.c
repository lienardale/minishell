/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 18:50:38 by alienard          #+#    #+#             */
/*   Updated: 2020/09/16 18:56:42 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strerror(t_cmd *cmd, t_sh *sh, char *str)
{
	if (sh->nbline)
		ft_dprintf(2, "%s: line %d: %s: %s: %s\n",
		sh->file, sh->nbline, cmd->cmd, cmd->av[1], str);
	else
		ft_dprintf(2, "minishell: %s: %s: %s\n",
		cmd->cmd, cmd->av[1], str);
	return (1);
}
