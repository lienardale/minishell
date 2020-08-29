/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 16:38:31 by alienard          #+#    #+#             */
/*   Updated: 2020/08/28 19:26:37 by alienard         ###   ########.fr       */
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

void	ft_exec_redir(t_sh *sh, t_cmd *cmd)
{
	cmd->redir == '<' ? ft_exec_redir_in(sh, cmd) : 0;
	cmd->redir == '>' ? ft_exec_redir_out(sh, cmd) : 0;
	cmd->redir == '2' ? ft_exec_append(sh, cmd) : 0;
}

int		ft_unexpected_token(char *inputs, t_sh *sh, int i)
{
	if (sh->nbline)
	{
		ft_dprintf(2, "%s: line %d: syntax error near unexpected token'%s'\n", sh->file, sh->nbline, &inputs[i]);
		ft_dprintf(2, "%s: line %d: '%s'\n", sh->file, sh->nbline, inputs);
	}
	else
	{
		ft_dprintf(2, "minishell: syntax error near unexpected token'%s'\n", &inputs[i]);
	}
	return (1);
}

int		ft_check_args(char *inputs, t_sh *sh)
{
	int	i;

	i = 0;
	while (inputs[i])
	{
		while (inputs[i] && ft_isspace(inputs[i]))
			i++;
		if (inputs[i] && !ft_isalnum(inputs[i]) && !ft_ischarset(META, inputs[i]) && ft_unexpected_token(inputs, sh, i))
			return (0);
		while (inputs[i] && (ft_isalnum(inputs[i]) || ft_isspace(inputs[i]) || ft_ischarset(META, inputs[i])))
			i++;
		if (ft_ischarset(END_CMD, inputs[i]))
			i++;
		// printf("input[i]:|%s|\n", &inputs[i]);
		i++;
	}
	return (1);
}
