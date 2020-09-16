/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:13:24 by alienard          #+#    #+#             */
/*   Updated: 2020/09/16 18:06:36 by alienard         ###   ########.fr       */
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

void	ft_init_args(t_sh *sh, char *line, int *i)
{
	int		j;
	char	*tmp;
	char	**tmp_av;
	char	**tmp_av2;
	t_cmd	*cmd;

	j = *i;
	cmd = (t_cmd *)(sh->cmds->tail->data);
	while (ft_isspace(line[j]) && !ft_isinquotes(line, j)
		&& !ft_is_escaped(line, j))
		j++;
	while (ft_isdigit(line[j]) && !ft_isinquotes(line, j)
		&& !ft_is_escaped(line, j))
		j++;
	if (ft_ischarset(REDIR, line[j]) && !ft_isinquotes(line, j)
		&& !ft_is_escaped(line, j))
	{
		*i = j;
		ft_handle_end(sh, line, i);
		return ;
	}
	ft_iterate_in_line(line, &j, END_CMD);
	if (ft_ischarset(REDIR, line[j]))
	{
		j--;
		while (j >= 0 && ft_isdigit(line[j]) && !ft_is_escaped(line, j))
			j--;
		if (ft_is_escaped(line, j))
		{
			ft_iterate_in_line(line, &j, REDIR);
			line[j++] = ' ';
			ft_iterate_in_line(line, &j, END_CMD);
		}
		tmp = ft_substr(line, *i, (j - *i));
		ft_iterate_in_line(line, &j, REDIR);
	}
	else
		tmp = ft_substr(line, *i, (j - *i));
	if (!tmp)
	{
		ft_dlst_delone(sh->cmds, ((t_dlist *)(sh->cmds->tail)));
		*i = j + 1;
		return ;
	}
	tmp_av = ft_split_quote(tmp, ' ');
	free(tmp);
	tmp_av2 = cmd->av;
	cmd->av = ft_dstrjoin(cmd->av, tmp_av);
	if (tmp_av2)
		ft_free_double_array(tmp_av2);
	if (tmp_av)
		ft_free_double_array(tmp_av);
	if (!(cmd->av) || !(cmd->av[0]))
	{
		ft_free_cmd(sh->cmds->tail);
		ft_dlst_delone(sh->cmds, ((t_dlist *)(sh->cmds->tail)));
		*i = j + 1;
		return ;
	}
	if (cmd->argv)
	{
		ft_lstclear(&cmd->argv, free);
		cmd->argv = NULL;
	}
	cmd->argv = ft_split_to_lst(cmd->av);
	cmd->ac = ft_double_strlen(cmd->av);
	if (cmd->cmd)
		free(cmd->cmd);
	cmd->cmd = ft_strdup(cmd->av[0]);
	*i = j;
	ft_handle_end(sh, line, i);
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
	if (sh->cmds)
		ft_lstclear_cmds(sh->cmds);
	ft_init_dlst(&sh->cmds);
	inputs = ft_strtrim_space(inputs);
	while (inputs[i])
		ft_init_cmd(sh, inputs, &i);
	free(inputs);
	inputs = NULL;
	return (1);
}
