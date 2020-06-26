/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:13:24 by alienard          #+#    #+#             */
/*   Updated: 2020/06/26 16:55:57 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

void	ft_handle_end(char *line, t_cmd *cmd)
{
	if (ft_ischarset(REDIR,line[0]))
		ft_parse_redir(line, cmd);
	else if (line[0] == ';')
		cmd->after = ';';
}

void	ft_handle_meta_char(char *line, t_cmd *cmd)
{
	if (line[0] == '\\' && line[1] != '\\')
		ft_parse_escape(line, cmd);
	else if (ft_ischarset(QUOTE, line[0]))
		ft_parse_quote(line, cmd);
	else if (line[0] == '-')
		ft_parse_opt(line, cmd);
	else if (line[0] == '$')
		ft_parse_wild(line, cmd);
}

void	ft_init_cmd(t_cmd *cmd, char *line, int *i)
{
	int		j;
	char	*tmp;

	j = *i;
	printf("i = %d\n", *i);
	while (line[j] && !ft_ischarset(END_CMD, line[j]))
		j++;
	cmd->after = line[j];
	tmp = ft_substr(line, *i, (j - *i));
	cmd->av = ft_split_quote(tmp, ' ');
	free(tmp);
	cmd->ac = ft_double_strlen(cmd->av);
	cmd->cmd= ft_strdup(cmd->av[0]);
	*i = j;
}


void	ft_line_to_lst(char *inputs, t_sh *sh)
{
	t_cmd	*content;
	// t_cmd	*lst_content;
	int		i;
	int		pos;
	int		before;

	i = -1;
	pos = 0;
	before = 0;
	ft_init_dlst(&sh->cmds);
	while (inputs[++i])
	{
		if (!(content = ft_calloc(1, sizeof(t_cmd))))
			return;
		while (ft_isspace(inputs[i]))
			i++;
		content->pos = pos;
		content->before = before;
		content->env = sh->env;
		ft_init_cmd(content, inputs, &i);
		ft_dlst_addback(sh->cmds, content);
		before = content->after;
		pos++;
	}
	i = -1;
}

char	**ft_split_line(char **inputs)
{
	char	**tokens;
	char	*tmp;
	char	*tmp_2;
	int		len;
	int		i;

	len = -1;
	i = 0;
	// tmp = inputs[0];
	tmp = NULL;
	//	Joining the inputs in case of multiline
	if (inputs && ft_double_strlen(inputs) > 0)
	{
		while (inputs[i])
		{
			tmp_2 = tmp;
			// carefull, join has been slightly modified for this to work, check it before merge :
			// when s1 == NULL, it returns ft_strdup(s2);
			tmp = ft_strjoin(tmp, inputs[i]);
			// freeing previous tmp
			ft_free_ptr(tmp_2);
			i++;
		}
	}
	// Spliting the outcome to get one cmd per char *
	tokens = ft_split_quote(tmp, ';');
	// freeing tmp one last time
	ft_free_ptr(tmp);
	if (!tokens)
	{
		ft_dprintf(2, "minishell: allocation error\n");
		exit(EXIT_FAILURE);
	}
	return (tokens);
}
