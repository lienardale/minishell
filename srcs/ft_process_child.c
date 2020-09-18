/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 11:08:40 by alienard          #+#    #+#             */
/*   Updated: 2020/09/18 11:11:36 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_process_child(t_cmd *cmd, t_sh *sh)
{
	int		status;
	char	**split_env;

	split_env = NULL;
	if (cmd->pipe_prev || cmd->pipe_next)
		cmd->ret_dup = ft_exec_pipe_child(sh, cmd);
	if (cmd->redir)
		ft_exec_redir(sh, cmd);
	split_env = ft_lst_env_to_split_launch(*(sh->env));
	status = ft_search_n_execute(cmd->av, split_env, sh);
	if (split_env)
		ft_free_split(split_env);
	if (cmd->redir)
		(close(cmd->fdout) < 0) ? ft_dprintf(2,
			"Close of fd_out not ok\n") : 0;
	return (status);
}
