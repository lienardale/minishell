/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 16:38:31 by alienard          #+#    #+#             */
/*   Updated: 2020/06/30 15:30:55 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

void	ft_parse_escape(int *j, char *line, t_cmd *cmd)
{
	int	i;

	i = 0;
	char	*beg;
	char	*end;
	// handeling case of "\\"
	cmd->bkslh = (cmd->bkslh == true) ? false : true;
	if (cmd->bkslh == false)
		return ;
	line[*j] = '\0';
	beg = ft_strdup(line);
	end = ft_strdup(&line[*j + 1]);
	free(line);
	line = ft_strjoin(beg, end);
	free(beg);
	free(end);
	// what to do then ?
	// echo "cou\"cou"
	// \l\s

	// cmd->bkslh = (cmd->bkslh == true) ? false : true;
}

void	ft_parse_redir(char *line, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (line[0] == '>')
	{
		cmd->after = '>';
		if (line[1] == '>')
			cmd->after = '2';
	}
	else if (line[0] == '<')
	{
		cmd->after = '<';
	}
	else if (line[0] == '|')
	{
		cmd->after = '|';
	}
}

void	ft_parse_quote(char *line, t_cmd *cmd)
{
	int	i;

	i = 0;
	(void)line;
	(void)cmd;
}

void	ft_parse_opt(char *line, t_cmd *cmd)
{
	int	i;

	i = 0;
	(void)line;
	(void)cmd;
}

void	ft_parse_wild(char *line, t_cmd *cmd)
{
	int	i;

	i = 0;
	(void)line;
	(void)cmd;
}
