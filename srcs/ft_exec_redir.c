/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 16:24:45 by alienard          #+#    #+#             */
/*   Updated: 2020/09/18 10:06:55 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_redir(t_sh *sh, t_cmd *cmd)
{
	cmd->redir == '<' ? ft_exec_redir_in(sh, cmd) : 0;
	cmd->redir == '>' ? ft_exec_redir_out(sh, cmd) : 0;
	cmd->redir == '2' ? ft_exec_append(sh, cmd) : 0;
}

int		ft_exec_redir_out(t_sh *sh, t_cmd *cmd)
{
	int	fd;

	fd = cmd->nb_redir != -1 ? cmd->nb_redir : STDOUT_FILENO;
	if ((cmd->fdout = open(cmd->file_redir, O_WRONLY | O_CREAT
		| O_TRUNC, 0777)) == -1)
		return (0);
	if ((cmd->ret_dup = dup2(cmd->fdout, fd)) < 0
		&& (write(1, "dup2 failed\n", ft_strlen("dup2 failed\n"))))
		return (ft_exit((t_cmd*)(sh->cmds->head), sh));
	return (1);
}

int		ft_exec_append(t_sh *sh, t_cmd *cmd)
{
	int	fd;

	fd = cmd->nb_redir != -1 ? cmd->nb_redir : STDOUT_FILENO;
	if ((cmd->fdout = open(cmd->file_redir, O_WRONLY | O_CREAT
		| O_APPEND, 0777)) == -1)
		return (0);
	if ((cmd->ret_dup = dup2(cmd->fdout, fd)) < 0
		&& (write(1, "dup2 failed\n", ft_strlen("dup2 failed\n"))))
		return (ft_exit((t_cmd*)(sh->cmds->head), sh));
	return (1);
}

int		ft_exec_redir_in(t_sh *sh, t_cmd *cmd)
{
	int	fd;

	fd = cmd->nb_redir != -1 ? cmd->nb_redir : STDIN_FILENO;
	cmd->fdin = open(cmd->file_redir, O_RDONLY);
	if ((cmd->ret_dup = dup2(cmd->fdin, fd)) < 0)
		return (ft_exit((t_cmd*)(sh->cmds->head), sh));
	return (1);
}
