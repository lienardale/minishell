/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 16:38:31 by alienard          #+#    #+#             */
/*   Updated: 2020/06/29 16:46:15 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

void	ft_parse_escape(char *line, t_cmd *cmd)
{
	int	i;

	i = 0;
	(void)line;
	(void)cmd;
}

void	ft_parse_redir(char *line, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (line[0] == '>')
	{
		if (line[1] == '>')
		{
			cmd->after = '2';
			return ;
		}
		cmd->after = '>';
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