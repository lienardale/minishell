/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reset_sh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 12:58:35 by cdai              #+#    #+#             */
/*   Updated: 2020/09/22 15:22:16 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_reset_sub_cmd(t_cmd *cmd)
{
	if (cmd->pipe_next)
	{
		ft_reset_sub_cmd(cmd->pipe_next);
		cmd->pipe_next = NULL;
	}
	cmd->after = 0;
	if (cmd->argv)
		ft_lstclear(&cmd->argv, free);
	if (cmd->av)
		ft_free_double_array(cmd->av);
	free(cmd->cmd);
	if (cmd->file_redir)
		ft_free_ptr(cmd->file_redir);
	if (cmd->fd_in)
		ft_lstclear(cmd->fd_in, free);
	if (cmd->fd_out)
		ft_lstclear(cmd->fd_out, free);
	free(cmd);
}

void	ft_reset_cmd(t_dlist *node)
{
	t_cmd	*cmd;

	if (!node || !node->data)
		return ;
	cmd = (t_cmd*)node->data;
	if (cmd->argv)
		ft_lstclear(&cmd->argv, free);
	if (cmd->av)
		ft_free_double_array(cmd->av);
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->file_redir)
		ft_free_ptr(cmd->file_redir);
	if (cmd->fd_in)
		ft_lstclear(cmd->fd_in, free);
	if (cmd->fd_out)
		ft_lstclear(cmd->fd_out, free);
	if (cmd->pipe_next)
	{
		ft_reset_sub_cmd(cmd->pipe_next);
		cmd->pipe_next = NULL;
	}
}

void	ft_reset_sh(t_sh *sh)
{
	t_dlist	*tmp;
	t_dlist	*tmp2;

	if (sh->cmds)
	{
		tmp = sh->cmds->head;
		tmp2 = sh->cmds->head;
		while (tmp)
		{
			tmp2 = tmp2->next;
			ft_reset_cmd(tmp);
			tmp = tmp2;
		}
	}
	ft_dlst_del(sh->cmds);
	free(sh->cmds);
	sh->cmds = NULL;
}
