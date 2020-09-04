/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 17:15:32 by alienard          #+#    #+#             */
/*   Updated: 2020/09/02 17:15:32 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_parse_redir_in(t_sh *sh, char *line, int *i)
{
	char	*tmp;
	int		j;
	int		fd;

	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	j = *i;
	while (line[j] && (!ft_isspace(line[j]) || ft_is_escaped(line, j)))
		j++;
	tmp = ft_substr(line, *i, j - *i);
	tmp = ft_strdup_clean(tmp);
	if ((fd = open(tmp, O_RDONLY)) == -1)
		sh->nbline ? ft_dprintf(2,
			"%s: line %d: %s: No such file or directory\n",
			sh->file, sh->nbline, tmp) 
			: ft_dprintf(2,
			"minishell: %s: No such file or directory\n", tmp);
	close(fd);
	while (line[j] && (!ft_isspace(line[j]) || ft_is_escaped(line, j)))
		j++;
	if (((t_cmd*)(sh->cmds->tail->data))->file_redir)
		free(((t_cmd*)(sh->cmds->tail->data))->file_redir);
	((t_cmd*)(sh->cmds->tail->data))->file_redir = tmp;
	*i = j;
	ft_init_args(sh, line, i);
	return (1);
}

int		ft_parse_redir_out(t_sh *sh, char *line, int *i)
{
	char	*tmp;
	int		j;
	int		fd;
	DIR		*dir;

	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	j = *i;
	while (line[j] && (!ft_isspace(line[j]) || ft_is_escaped(line, j)))
		j++;
	tmp = ft_substr(line, *i, j - *i);
	tmp = ft_strdup_clean(tmp);
	if ((fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0777)) == -1)
	{
		if ((dir = opendir(tmp)) && sh->nbline)
			ft_dprintf(2, "%s: line %d: %s: Is a directory\n",
				sh->file, sh->nbline, tmp);
		else if ((dir = opendir(tmp)))
			ft_dprintf(2, "bash: %s: Is a directory\n", tmp);
		else if (sh->nbline)
			ft_dprintf(2, "%s: line %d: %s: No such file or directory\n",
				sh->file, sh->nbline, tmp);
		else
			ft_dprintf(2, "bash: %s: No such file or directory\n", tmp);
		while (line[j])
		{
			if (ft_ischarset(END_CMD, line[j]) && !ft_isinquotes(line, j)
				&& !ft_is_escaped(line, j))
				break ;
			j++;
		}
		*i = j + 1;
		return (0);
	}
	close(fd);
	while (line[j] && (!ft_isspace(line[j]) || ft_is_escaped(line, j)))
		j++;
	if (((t_cmd*)(sh->cmds->tail->data))->file_redir)
		free(((t_cmd*)(sh->cmds->tail->data))->file_redir);
	((t_cmd*)(sh->cmds->tail->data))->file_redir = tmp;
	*i = j;
	ft_init_args(sh, line, i);
	return (1);
}

int		ft_parse_append(t_sh *sh, char *line, int *i)
{
	char	*tmp;
	int		j;
	int		fd;
	DIR		*dir;

	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	j = *i;
	while (line[j] && (!ft_isspace(line[j]) || ft_is_escaped(line, j)))
		j++;
	tmp = ft_substr(line, *i, j - *i);
	tmp = ft_strdup_clean(tmp);
	if ((fd = open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0777)) == -1)
	{
		if ((dir = opendir(tmp)) && sh->nbline)
			ft_dprintf(2, "%s: line %d: %s: Is a directory\n",
				sh->file, sh->nbline, tmp);
		else if ((dir = opendir(tmp)))
			ft_dprintf(2, "bash: %s: Is a directory\n", tmp);
		else if (sh->nbline)
			ft_dprintf(2, "%s: line %d: %s: No such file or directory\n",
				sh->file, sh->nbline, tmp);
		else
			ft_dprintf(2, "bash: %s: No such file or directory\n", tmp);
		while (line[j])
		{
			if (ft_ischarset(END_CMD, line[j]) && !ft_isinquotes(line, j)
				&& !ft_is_escaped(line, j))
				break ;
			j++;
		}
		*i = j + 1;
		return (0);
	}
	close(fd);
	while (line[j] && (!ft_isspace(line[j]) || ft_is_escaped(line, j)))
		j++;
	if (((t_cmd*)(sh->cmds->tail->data))->file_redir)
		free(((t_cmd*)(sh->cmds->tail->data))->file_redir);
	((t_cmd*)(sh->cmds->tail->data))->file_redir = tmp;
	*i = j;
	ft_init_args(sh, line, i);
	return (1);
}
