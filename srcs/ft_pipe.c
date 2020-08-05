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
	tmp->pipe_prev = ((t_cmd *)(next->data));
	((t_cmd *)(next->data))->pipe_next = tmp;
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
	if (!(cmd->pipe_next))
	{
		close(cmd->pipe_prev->pipedfd[0]);
		if ((cmd->ret_dup = dup2(cmd->pipe_prev->pipedfd[1], STDOUT_FILENO)) < 0)
			write(1, "dup2 failed\n", ft_strlen("dup2 failed\n"));
		close(cmd->pipe_prev->pipedfd[1]);
	}
	else
	{
		close(cmd->pipedfd[1]);
		if ((cmd->ret_dup = dup2(cmd->pipedfd[0], STDIN_FILENO)) < 0)
			write(1, "dup2 failed\n", ft_strlen("dup2 failed\n"));
		close(cmd->pipedfd[0]);
	}
	return (0);
}

int		ft_exec_pipe_parent(t_sh *sh, t_cmd *cmd)
{
	(void)sh;
	if (cmd->pipe_next)
	{
		close(cmd->pipedfd[0]);
		dup2(cmd->pipedfd[1], STDIN_FILENO);
		close(cmd->pipedfd[1]);
	}
	else
	{
		close(cmd->pipedfd[1]);
		dup2(cmd->pipedfd[0], STDIN_FILENO); 
		close(cmd->pipedfd[0]);
	}
	return (0);
}
