/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 15:23:12 by alienard          #+#    #+#             */
/*   Updated: 2020/08/04 15:23:12 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int		ft_add_pipe(t_dlist *cur, t_dlist *next, t_sh *sh)
{
	t_cmd	*tmp;

	tmp = ((t_cmd *)(cur->data));
	tmp->piped_out = ((t_cmd *)(next->data));
	((t_cmd *)(next->data))->piped_in = tmp;
	next->prev = cur->prev;
	if (cur->prev)
		cur->prev->next = next;
	else
		sh->cmds->head = next;
	return (0);
}

int		ft_create_pipe(t_sh *sh)
{
	t_dlist	*cur;

	cur = sh->cmds->head;
	while (cur)
	{
		if (((t_cmd *)(cur->data))->after == '|')
			ft_add_pipe(cur, cur->next, sh);
		cur = cur->next;
	}
	return (0);
}

int		ft_init_pipe(t_sh *sh, t_cmd *cmd)
{
	(void)sh;
	if (pipe(cmd->pipedfd) < 0)
	{
		ft_dprintf(2, "Pipe failed to initialize\n");
		return (0);
	}
	// cmd->pipedfd[0] = cmd->piped_in->pipedfd[1];
	// dup2(cmd->pipedfd[0], cmd->piped_in->pipedfd[1]);
	return (1);
}

int		ft_exec_pipe_child(t_sh *sh, t_cmd *cmd)
{
	(void)sh;
	close(cmd->pipedfd[0]);
	dup2(cmd->pipedfd[1], STDOUT_FILENO);
	close(cmd->pipedfd[1]);
	return (0);
}

int		ft_exec_pipe_parent(t_sh *sh, t_cmd *cmd)
{
	(void)sh;
	close(cmd->pipedfd[1]); 
	dup2(cmd->pipedfd[0], STDIN_FILENO); 
	close(cmd->pipedfd[0]);
	return (0);
}
