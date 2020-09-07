/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:13:24 by alienard          #+#    #+#             */
/*   Updated: 2020/09/07 18:02:43 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_end(t_sh *sh, char *line, int *i)
{
	if (ft_ischarset(REDIR, line[*i]))
	{
		if (!ft_parse_redir(sh, line, i))
		{
			// if bash execs after, stays commented, if not, uncomment
			// while (line[*i])
				// (*i)++;
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
	t_cmd	*cmd;

	j = *i;
	cmd = (t_cmd *)(sh->cmds->tail->data);
	while (ft_isspace(line[j]) && !ft_isinquotes(line, j)
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
		while (j >= 0 && ft_isdigit(line[j]))
			j--;
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
	cmd->av = cmd->av ? ft_dstrjoin(cmd->av, tmp_av) : tmp_av;
	if (!(cmd->av) || !(cmd->av[0]))
	{
		ft_dlst_delone(sh->cmds, ((t_dlist *)(sh->cmds->tail)));
		*i = j + 1;
		return ;
	}
	cmd->argv = ft_split_to_lst(cmd->av);
	cmd->ac = ft_double_strlen(cmd->av);
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
	ft_init_dlst(&sh->cmds);
	inputs = ft_strtrim_space(inputs);
	while (inputs[i])
		ft_init_cmd(sh, inputs, &i);
	ft_free_ptr(inputs);
	return (1);
}
