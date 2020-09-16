/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 16:38:31 by alienard          #+#    #+#             */
/*   Updated: 2020/09/16 18:01:52 by alienard         ###   ########.fr       */
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
		if (line[*i] == '>')
		{
			*i += 1;
			((t_cmd*)(sh->cmds->tail->data))->redir = '2';
		}
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

void	ft_exec_redir(t_sh *sh, t_cmd *cmd)
{
	cmd->redir == '<' ? ft_exec_redir_in(sh, cmd) : 0;
	cmd->redir == '>' ? ft_exec_redir_out(sh, cmd) : 0;
	cmd->redir == '2' ? ft_exec_append(sh, cmd) : 0;
}

int		ft_unexpected_token(char *inputs, t_sh *sh, int i)
{
	char	token[8];

	ft_strlcpy(token, &inputs[i], 3);
	if (ft_isspace(token[1]))
		token[1] = '\0';
	if (ft_ischarset(REDIR, inputs[i]))
		ft_strlcpy(token, "newline", 8);
	if (sh->nbline)
	{
		ft_dprintf(2, "%s: line %d: syntax error near unexpected token `%s'\n",
			sh->file, sh->nbline, token);
		ft_dprintf(2, "%s: line %d: `%s'\n", sh->file, sh->nbline, inputs);
	}
	else
		ft_dprintf(2, "minishell: syntax error near unexpected token `%s'\n",
			token);
	sh->ret_cmd = 2;
	free(inputs);
	inputs = NULL;
	return (0);
}

int		ft_check_args(char *inputs, t_sh *sh)
{
	int	i;

	i = 0;
	while (inputs[i])
	{
		while (inputs[i] && ft_isspace(inputs[i]))
			i++;
		if (inputs[i] && !ft_isalnum(inputs[i])
			&& !ft_ischarset(META, inputs[i]) && !ft_is_escaped(inputs, i)
			&& !ft_isinquotes(inputs, i))
			return (ft_unexpected_token(inputs, sh, i));
		while (inputs[i] && (!ft_ischarset(END_CMD, inputs[i])
			|| ft_isinquotes(inputs, i) || ft_is_escaped(inputs, i)))
			i++;
		if (inputs[i] && ft_ischarset(END_CMD, inputs[i]))
			i++;
		if (inputs[i] && inputs[i - 1] == '>' && inputs[i] == '>')
			i++;
	}
	i--;
	while (i > 0 && ft_isspace(inputs[i]))
		i--;
	if (inputs[i] && ft_ischarset(REDIR, inputs[i]))
		return (ft_unexpected_token(inputs, sh, i));
	return (1);
}

char	*ft_strtrim_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) && !ft_is_escaped(str, i)
			&& !ft_isinquotes(str, i))
			str[i] = ' ';
		i++;
	}
	return (str);
}

int		ft_iterate_in_line(char *line, int *j, char *set)
{
	while (line[*j])
	{
		if (ft_ischarset(set, line[*j]) && !ft_isinquotes(line, *j)
			&& !ft_is_escaped(line, *j))
			break ;
		(*j)++;
	}
	return (1);
}

int		ft_iterate_in_line_redir(char *line, int *j, char *set)
{
	while (line[*j] && (!ft_isspace(line[*j]) || ft_is_escaped(line, *j)))
	{
		if (ft_ischarset(set, line[*j]) && !ft_isinquotes(line, *j)
			&& !ft_is_escaped(line, *j))
			break ;
		(*j)++;
	}
	return (1);
}
