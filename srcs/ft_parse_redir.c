/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 17:19:41 by alienard          #+#    #+#             */
/*   Updated: 2020/07/11 17:19:41 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

void	ft_parse_redir_in(t_sh *sh, char *line, int *i)
{
	(void)sh;
	(void)line;
	(void)i;
}

void	ft_parse_redir_out(t_sh *sh, char *line, int *i)
{
	char	*tmp;
	int		j;
	int 	fd;

	while (ft_isspace(line[*i]))
		(*i)++;
	j = *i;
	while (!ft_isspace(line[j]) || ft_isescaped(&line[j]))
		j++;
	tmp = ft_substr(line, *i, j);
	if ((fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0777)) == -1)
	{
		ft_dprintf(2, "Error in open.");
		return ;
	}
	ft_lstadd_back(((t_cmd*)(sh->cmds->tail->data))->fd_out, ft_lstnew(&fd));
	while (line[j])
	{
		if (ft_ischarset(END_CMD, line[j]) && !ft_isinquotes(line, j))
			break ;
		j++;
	}
	*i = j;
	if (ft_ischarset(REDIR, line[j]))
		ft_parse_redir(sh, line, i);
	
}

void	ft_parse_append(t_sh *sh, char *line, int *i)
{
	char	*tmp;
	int		j;

	while (ft_isspace(line[*i]))
		(*i)++;
	j = *i;
	while (!ft_isspace(line[j]) || ft_isescaped(&line[j]))
		j++;
	tmp = ft_substr(line, *i, j);
	if ((((t_cmd*)(sh->cmds->tail->data))->fd_out =
		open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0777)) == -1)
	{
		ft_dprintf(2, "Error in open.");
		return ;
	}
	while (line[j])
	{
		if (ft_ischarset(END_CMD, line[j]) && !ft_isinquotes(line, j))
			break ;
		j++;
	}
	*i = j;
	if (ft_ischarset(REDIR, line[j]))
		ft_parse_redir(sh, line, i);
}
