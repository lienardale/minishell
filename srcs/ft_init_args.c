/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 13:15:18 by alienard          #+#    #+#             */
/*   Updated: 2020/09/18 14:53:25 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_search_redir(int *i, int *j, char *line, t_sh *sh)
{
	while (ft_isspace(line[*j]) && !ft_isinquotes(line, *j)
		&& !ft_is_escaped(line, *j))
		(*j)++;
	while (ft_isdigit(line[*j]) && !ft_isinquotes(line, *j)
		&& !ft_is_escaped(line, *j))
		(*j)++;
	if (ft_ischarset(REDIR, line[*j]) && !ft_isinquotes(line, *j)
		&& !ft_is_escaped(line, *j))
	{
		*i = *j;
		ft_handle_end(sh, line, i);
		return (1);
	}
	return (0);
}

static char	*ft_isredir(int *i, int *j, char *line)
{
	char	*tmp;

	(*j)--;
	while (*j >= 0 && ft_isdigit(line[*j]) && !ft_is_escaped(line, *j))
		(*j)--;
	if (ft_is_escaped(line, *j))
	{
		ft_iterate_in_line(line, j, REDIR);
		line[(*j)++] = ' ';
		ft_iterate_in_line(line, j, END_CMD);
	}
	tmp = ft_substr(line, *i, (*j - *i));
	ft_iterate_in_line(line, j, REDIR);
	return (tmp);
}

static int	ft_join_args(t_sh *sh, t_cmd *cmd, char **tmp)
{
	char	**tmp_av;
	char	**tmp_av2;

	tmp_av = ft_split_quote(*tmp, ' ');
	ft_safe_free((void**)tmp);
	tmp_av2 = cmd->av;
	cmd->av = ft_dstrjoin(cmd->av, tmp_av);
	(tmp_av2) ? ft_free_double_array(tmp_av2) : 0;
	(tmp_av) ? ft_free_double_array(tmp_av) : 0;
	if (!(cmd->av) || !(cmd->av[0]))
	{
		ft_free_cmd(sh->cmds->tail);
		ft_dlst_delone(sh->cmds, ((t_dlist *)(sh->cmds->tail)));
		return (1);
	}
	return (0);
}

void		ft_finish_init_args(t_cmd *cmd)
{
	cmd->argv = ft_split_to_lst(cmd->av);
	cmd->ac = ft_double_strlen(cmd->av);
	(cmd->cmd) ? ft_safe_free((void**)&cmd->cmd) : 0;
	cmd->cmd = ft_strdup(cmd->av[0]);
}

void		ft_init_args(t_sh *sh, char *line, int *i)
{
	int		j;
	char	*tmp;
	t_cmd	*cmd;

	j = *i;
	cmd = (t_cmd *)(sh->cmds->tail->data);
	if (ft_search_redir(i, &j, line, sh))
		return ;
	ft_iterate_in_line(line, &j, END_CMD);
	tmp = (ft_ischarset(REDIR, line[j])) ? ft_isredir(i, &j, line) :
			ft_substr(line, *i, (j - *i));
	if (!tmp)
	{
		ft_dlst_delone(sh->cmds, ((t_dlist *)(sh->cmds->tail)));
		*i = j + 1;
		return ;
	}
	if (ft_join_args(sh, cmd, &tmp) && (*i = j + 1))
		return ;
	if (cmd->argv)
		ft_lstclear(&cmd->argv, free);
	ft_finish_init_args(cmd);
	*i = j;
	ft_handle_end(sh, line, i);
}
