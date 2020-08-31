/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:41:18 by cdai              #+#    #+#             */
/*   Updated: 2020/08/31 16:54:16 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

void	ft_clear_cmds(t_ref *cmds)
{
	t_dlist	*dlst;
	t_cmd	*cmd;

	dlst = cmds->head;
	while (dlst)
	{
		cmd = dlst->data;
		while (cmd)
		{
			free(cmd->cmd);
			ft_free_split(cmd->av);
			cmd = cmd->pipe_next;
		}
		dlst = dlst->next;
	}
}
