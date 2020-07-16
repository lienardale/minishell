/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 16:38:31 by alienard          #+#    #+#             */
/*   Updated: 2020/07/15 11:18:03 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

void	ft_parse_redir(t_sh *sh, char *line, int *i)
{
	// t_cmd *cmd;

	// cmd = ((t_cmd*)(sh->cmds->tail->data));
	if (line[*i] == '>' && (*i += 1))
	{
		((t_cmd*)(sh->cmds->tail->data))->after = '>';
		if (line[*i] == '>' && (*i += 1))
			((t_cmd*)(sh->cmds->tail->data))->after = '2';
	}
	else if (line[*i] == '<' && (*i += 1))
		((t_cmd*)(sh->cmds->tail->data))->after = '<';
	((t_cmd*)(sh->cmds->tail->data))->after == '<' ?
	ft_parse_redir_in(sh, line, i) : 0;
	((t_cmd*)(sh->cmds->tail->data))->after == '>' ?
	ft_parse_redir_out(sh, line, i)
	: ft_parse_append(sh, line, i);
}

void	ft_parse_pipe(t_sh *sh, char *line, int *i)
{
	(void)line;
	(void)i;
	((t_cmd*)(sh->cmds->tail->data))->after = '|';
}
