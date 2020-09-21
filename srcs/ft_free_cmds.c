/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 14:57:31 by alienard          #+#    #+#             */
/*   Updated: 2020/09/21 11:38:08 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_free_sub_cmd(t_cmd *cmd)
{
	if (cmd->pipe_next)
		ft_free_sub_cmd(cmd->pipe_next);
	if (cmd->argv)
		ft_lstclear(&cmd->argv, free);
	if (cmd->av)
		ft_free_double_array(cmd->av);
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->file_redir)
		free(cmd->file_redir);
	if (cmd->fd_in)
		ft_lstclear(cmd->fd_in, free);
	if (cmd->fd_out)
		ft_lstclear(cmd->fd_out, free);
	if (cmd)
		free(cmd);
}

void		ft_free_cmd(t_dlist *node)
{
	t_cmd	*cmd;

	if (!node || !node->data)
		return ;
	cmd = (t_cmd*)node->data;
	if (!cmd)
		return ;
	if (cmd->argv)
		ft_lstclear(&cmd->argv, free);
	if (cmd->av)
		ft_free_double_array(cmd->av);
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->file_redir)
		free(cmd->file_redir);
	if (cmd->fd_in)
		ft_lstclear(cmd->fd_in, free);
	if (cmd->fd_out)
		ft_lstclear(cmd->fd_out, free);
	if (cmd->pipe_next)
		ft_free_sub_cmd(cmd->pipe_next);
}

void		ft_lstclear_cmds(t_ref *cmds)
{
	t_dlist	*tmp;
	t_dlist	*tmp2;

	if (cmds == NULL || cmds->head == NULL)
		return ;
	tmp = cmds->head;
	tmp2 = cmds->head;
	while (tmp)
	{
		tmp2 = tmp2->next;
		ft_free_cmd(tmp);
		tmp = tmp2;
	}
}
