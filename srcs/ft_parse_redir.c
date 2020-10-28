/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 10:09:34 by alienard          #+#    #+#             */
/*   Updated: 2020/10/28 17:14:32 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_parse_redir_nb(t_sh *sh, char *line, int *i)
{
	int		j;
	char	*tmp;

	j = *i;
	j--;
	while (j >= 0 && ft_isdigit(line[j]))
		j--;
	if (line[j - 1] && line[j - 1] == '-')
		j--;
	if (!(tmp = ft_substr(line, j + 1, *i - j - 1)))
		return (0);
	if (!ft_is_escaped(line, j) && tmp[0] != '-' && ft_isdigit(tmp[0]))
		((t_cmd*)(sh->cmds->tail->data))->nb_redir = ft_atoi(tmp);
	else
		((t_cmd*)(sh->cmds->tail->data))->nb_redir = -1;
	free(tmp);
	return (1);
}

int		ft_parse_redir(t_sh *sh, char *line, int *i)
{
	int		ret;

	ret = 1;
	if (!(ft_parse_redir_nb(sh, line, i)))
		ret = 0;
	if (line[*i] == '>')
	{
		*i += 1;
		((t_cmd*)(sh->cmds->tail->data))->redir = '>';
		if (line[*i] == '>' && (*i += 1))
			((t_cmd*)(sh->cmds->tail->data))->redir = '2';
	}
	else if (line[*i] == '<')
	{
		*i += 1;
		((t_cmd*)(sh->cmds->tail->data))->redir = '<';
	}
	if (ret && ((t_cmd*)(sh->cmds->tail->data))->redir == '<')
		return (ft_parse_redir_in(sh, line, i));
	else if (ret && ((t_cmd*)(sh->cmds->tail->data))->redir == '>')
		return (ft_parse_redir_out(sh, line, i));
	else if (ret && ((t_cmd*)(sh->cmds->tail->data))->redir == '2')
		return (ft_parse_append(sh, line, i));
	return (ret);
}

int		ft_parse_redir_in(t_sh *sh, char *line, int *i)
{
	char	*tmp;
	int		j;
	int		fd;

	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	j = *i;
	ft_iterate_in_line_redir(line, &j, END_CMD);
	tmp = ft_substr(line, *i, j - *i);
	tmp = ft_strdup_clean(tmp);
	if ((fd = open(tmp, O_RDONLY)) == -1)
		ft_redirerror(sh, tmp, "No such file or directory");
	close(fd);
	ft_iterate_in_line_redir(line, &j, END_CMD);
	if (((t_cmd*)(sh->cmds->tail->data))->file_redir)
		free(((t_cmd*)(sh->cmds->tail->data))->file_redir);
	((t_cmd*)(sh->cmds->tail->data))->file_redir = ft_strdup(tmp);
	while (line[j] && ft_isspace(line[j]) && !ft_is_escaped(line, j))
		j++;
	*i = j;
	ft_safe_free((void**)&tmp);
	ft_init_args(sh, line, i);
	return (1);
}

int		ft_parse_redir_out(t_sh *sh, char *line, int *i)
{
	char	*tmp;
	int		j;
	int		fd;
	DIR		*dir;

	ft_iterate_in_line_space(line, i);
	j = *i;
	ft_iterate_in_line_redir(line, &j, END_CMD);
	tmp = ft_strdup_clean(ft_substr(line, *i, j - *i));
	if ((fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0664)) == -1)
	{
		ft_redir_indir_error(sh, tmp, &dir);
		ft_iterate_in_line(line, &j, END_CMD);
		*i = j + 1;
		return (0);
	}
	close(fd);
	ft_iterate_in_line_redir(line, &j, END_CMD);
	ft_safe_free((void**)&((t_cmd*)(sh->cmds->tail->data))->file_redir);
	((t_cmd*)(sh->cmds->tail->data))->file_redir = ft_strdup(tmp);
	ft_iterate_in_line_space_esc(line, &j);
	*i = j;
	ft_safe_free((void**)&tmp);
	ft_init_args(sh, line, i);
	return (1);
}

int		ft_parse_append(t_sh *sh, char *line, int *i)
{
	char	*tmp;
	int		j;
	int		fd;
	DIR		*dir;

	ft_iterate_in_line_space(line, i);
	j = *i;
	ft_iterate_in_line_redir(line, &j, END_CMD);
	tmp = ft_strdup_clean(ft_substr(line, *i, j - *i));
	if ((fd = open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0664)) == -1)
	{
		ft_redir_indir_error(sh, tmp, &dir);
		ft_iterate_in_line(line, &j, END_CMD);
		*i = j + 1;
		return (0);
	}
	close(fd);
	ft_iterate_in_line_redir(line, &j, END_CMD);
	ft_safe_free((void**)&((t_cmd*)(sh->cmds->tail->data))->file_redir);
	((t_cmd*)(sh->cmds->tail->data))->file_redir = ft_strdup(tmp);
	ft_iterate_in_line_space_esc(line, &j);
	*i = j;
	ft_safe_free((void**)&tmp);
	ft_init_args(sh, line, i);
	return (1);
}
