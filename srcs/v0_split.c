/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:13:24 by alienard          #+#    #+#             */
/*   Updated: 2020/08/29 16:23:09 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

void	ft_handle_end(t_sh *sh, char *line, int *i)
{
	if (ft_ischarset(REDIR, line[*i]))
		ft_parse_redir(sh, line, i);
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
	// ft_printf("line:|%s|\n", &line[j]);
	while (line[j])
	{
		if (ft_ischarset(END_CMD, line[j]) && !ft_isinquotes(line, j)
			&& !ft_is_escaped(line, j))
			break ;
		j++;
	}
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
	// *i = -1;
	// while (cmd->av[++(*i)])
	// 	cmd->av[*i] = ft_strdup_clean(cmd->av[*i]);
	cmd->ac = ft_double_strlen(cmd->av);
	cmd->cmd= ft_strdup(cmd->av[0]);
	*i = j;
	ft_handle_end(sh, line, i);
}

void	ft_init_cmd(t_sh *sh, char *line, int *i)
{
	t_cmd	*cmd;

	if (!(cmd = ft_calloc(1, sizeof(t_cmd))))
		return;
	if (sh->cmds->tail && sh->cmds->tail->data)
	{
		cmd->pos = ((t_cmd*)(sh->cmds->tail->data))->pos + 1;
		cmd->before = ((t_cmd*)(sh->cmds->tail->data))->after;
		cmd->fdout = -1;
		cmd->ret_dup = -1;
	}
	ft_dlst_addback(sh->cmds, cmd);
	cmd->env = sh->env;
	ft_init_args(sh, line, i);
	// ft_print_double_array(cmd->av, "args in init cmd");
}

int		ft_line_to_lst(char *inputs, t_sh *sh)
{
	int		i;

	i = 0;
	if (!ft_check_args(inputs, sh))
		return (0);
	ft_init_dlst(&sh->cmds);
	while (inputs[i])
		ft_init_cmd(sh, inputs, &i);
	ft_free_ptr(inputs);
	return (1);
}
