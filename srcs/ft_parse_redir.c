/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 12:35:16 by alienard          #+#    #+#             */
/*   Updated: 2020/07/29 12:35:16 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

void	ft_parse_redir_in(t_sh *sh, char *line, int *i)
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
		ft_dprintf(2, "minishell: %s: No such file or directory\n", tmp);
	close(fd);
	while (line[j] && (!ft_isspace(line[j]) || ft_is_escaped(line, j)))
		j++;
	if (((t_cmd*)(sh->cmds->tail->data))->file_redir)
		free(((t_cmd*)(sh->cmds->tail->data))->file_redir);
	((t_cmd*)(sh->cmds->tail->data))->file_redir = tmp;
	*i = j;
	ft_init_args(sh, line, i);
}

void	ft_parse_redir_out(t_sh *sh, char *line, int *i)
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
	if ((fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0777)) == -1)
	{
		// ft_dprintf(2, "Error in open parse_redir_out.\n");
		return ;
	}
	close(fd);
	while (line[j] && (!ft_isspace(line[j]) || ft_is_escaped(line, j)))
		j++;
	if (((t_cmd*)(sh->cmds->tail->data))->file_redir)
		free(((t_cmd*)(sh->cmds->tail->data))->file_redir);
	((t_cmd*)(sh->cmds->tail->data))->file_redir = tmp;
	*i = j;
	ft_init_args(sh, line, i);
}

void	ft_parse_append(t_sh *sh, char *line, int *i)
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
	if ((fd = open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0777)) == -1)
	{
		// ft_dprintf(2, "Error in open parse_append.\n");
		return ;
	}
	close(fd);
	while (line[j] && (!ft_isspace(line[j]) || ft_is_escaped(line, j)))
		j++;
	if (((t_cmd*)(sh->cmds->tail->data))->file_redir)
		free(((t_cmd*)(sh->cmds->tail->data))->file_redir);
	((t_cmd*)(sh->cmds->tail->data))->file_redir = tmp;
	*i = j;
	ft_init_args(sh, line, i);
}
