/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 16:38:31 by alienard          #+#    #+#             */
/*   Updated: 2020/07/29 16:05:07 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

void	ft_parse_redir(t_sh *sh, char *line, int *i)
{
	if (line[*i] == '>')
	{
		*i += 1;
		((t_cmd*)(sh->cmds->tail->data))->redir = '>';
		if (line[*i] == '>')
		{
			*i += 1;
			((t_cmd*)(sh->cmds->tail->data))->redir = '2';
		}
	}
	else if (line[*i] == '<')
	{
		*i += 1;
		((t_cmd*)(sh->cmds->tail->data))->redir = '<';
	}
	((t_cmd*)(sh->cmds->tail->data))->redir == '<' ?
	ft_parse_redir_in(sh, line, i) : 0;
	((t_cmd*)(sh->cmds->tail->data))->redir == '>' ?
	ft_parse_redir_out(sh, line, i) : 0;
	((t_cmd*)(sh->cmds->tail->data))->redir == '2' ?
	ft_parse_append(sh, line, i) : 0;
}

void	ft_parse_pipe(t_sh *sh, char *line, int *i)
{
	(void)line;
	(void)i;
	((t_cmd*)(sh->cmds->tail->data))->after = '|';
}

void	ft_exec_redir(t_sh *sh, t_cmd *cmd)
{
	cmd->redir == '<' ? ft_exec_redir_in(sh, cmd) : 0;
	cmd->redir == '>' ? ft_exec_redir_out(sh, cmd) : 0;
	cmd->redir == '2' ? ft_exec_append(sh, cmd) : 0;
}
