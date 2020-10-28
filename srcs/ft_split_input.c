/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:13:24 by alienard          #+#    #+#             */
/*   Updated: 2020/10/28 17:18:49 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_end(t_sh *sh, char *line, int *i)
{
	if (ft_ischarset(REDIR, line[*i]))
	{
		if (!ft_parse_redir(sh, line, i))
		{
			ft_lstclear(&((t_cmd *)(sh->cmds->tail->data))->argv, free);
			((t_cmd *)(sh->cmds->tail->data))->argv = NULL;
			return ;
		}
	}
	else if (line[*i] == '|' && ((*i)++))
		((t_cmd*)(sh->cmds->tail->data))->after = '|';
	else if (line[*i] == ';' && ((*i)++))
		((t_cmd*)(sh->cmds->tail->data))->after = ';';
	else
		((t_cmd*)(sh->cmds->tail->data))->after = '\0';
}

void	ft_init_cmd(t_sh *sh, char *line, int *i)
{
	t_cmd	*cmd;

	if (!(cmd = ft_calloc(1, sizeof(t_cmd))))
		return ;
	if (sh->cmds->tail && sh->cmds->tail->data)
	{
		cmd->pos = ((t_cmd*)(sh->cmds->tail->data))->pos + 1;
		cmd->before = ((t_cmd*)(sh->cmds->tail->data))->after;
		cmd->fdout = -1;
		cmd->ret_dup = -1;
		cmd->nb_redir = -1;
	}
	ft_dlst_addback(sh->cmds, cmd);
	cmd->env = sh->env;
	ft_init_args(sh, line, i);
}

int		ft_line_to_lst(char *inputs, t_sh *sh)
{
	int		i;

	i = 0;
	if (!ft_check_args(inputs, sh))
		return (0);
	if (ft_strisspace(inputs))
	{
		free(inputs);
		inputs = NULL;
		return (2);
	}
	if (sh->cmds)
		ft_lstclear_cmds(sh->cmds);
	ft_init_dlst(&sh->cmds);
	inputs = ft_strtrim_space(inputs);
	while (inputs[i])
		ft_init_cmd(sh, inputs, &i);
	if (inputs)
		free(inputs);
	inputs = NULL;
	return (1);
}
