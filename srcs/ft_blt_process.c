/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_blt_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 16:10:35 by alienard          #+#    #+#             */
/*   Updated: 2020/09/17 17:49:07 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_blt_process_child(t_sh *sh, t_cmd *cmd,
			int (*fn)(t_cmd *cmd, t_sh *sh))
{
	if (cmd->pipe_prev || cmd->pipe_next)
		ft_exec_pipe_child(sh, cmd);
	if (cmd->redir)
		ft_exec_redir(sh, cmd);
	sh->ret_cmd = fn(cmd, sh);
	exit(sh->ret_cmd);
	return (sh->ret_cmd);
}

int			ft_blt_process(t_sh *sh, t_cmd *cmd,
			int (*fn)(t_cmd *cmd, t_sh *sh))
{
	pid_t	child;
	pid_t	wpid;
	int		status;

	child = fork();
	if (child < 0 && ft_dprintf(2, "Error forking\n"))
		return (0);
	else if (child > 0)
	{
		if (cmd->pipe_prev || cmd->pipe_next)
			ft_exec_pipe_parent(sh, cmd);
		wpid = waitpid(child, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(child, &status, WUNTRACED);
		return (status / 256);
	}
	else
		return (ft_blt_process_child(sh, cmd, fn));
	return (sh->ret_cmd);
}
