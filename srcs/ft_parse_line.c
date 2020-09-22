/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 16:38:31 by alienard          #+#    #+#             */
/*   Updated: 2020/09/22 15:15:58 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	(i > 0) ? i-- : 0;
	while (i > 0 && ft_isspace(inputs[i]))
		i--;
	if (inputs[i] && ft_ischarset(REDIR, inputs[i]))
		return (ft_unexpected_token(inputs, sh, i));
	return (1);
}

int		ft_strisspace(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i])
		return (0);
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
