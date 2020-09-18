/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:14:14 by alienard          #+#    #+#             */
/*   Updated: 2020/09/18 12:30:38 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_input_join(t_list *inputs)
{
	char	*tmp;
	char	*tmp_2;
	int		i;

	i = -1;
	tmp = NULL;
	if (inputs && ft_lstsize(inputs) > 0)
	{
		while (inputs)
		{
			tmp_2 = tmp;
			tmp = ft_strjoin(tmp, inputs->content);
			free(tmp_2);
			tmp_2 = NULL;
			inputs = inputs->next;
		}
	}
	if (!tmp)
	{
		ft_dprintf(2, "minishell: allocation error\n");
		exit(EXIT_FAILURE);
	}
	return (tmp);
}

void		ft_check_line(char **line, int *quote, int *bkslh)
{
	int		pos;
	int		nbquote;
	char	*tmp;

	pos = -1;
	nbquote = (*quote == 0) ? 0 : 1;
	while ((*line)[++pos])
	{
		if (((*line)[pos] == '\\' && *quote != '\'') || *bkslh == 1)
			(*bkslh)++;
		if ((*line)[pos] == '\'' && (*quote == '\'' || *quote == 0)
			&& *bkslh == 0 && (*quote = '\''))
			nbquote++;
		if ((*line)[pos] == '\"' && (*quote == '\"' || *quote == 0)
			&& *bkslh == 0 && (*quote = '\"'))
			nbquote++;
		*quote = (nbquote % 2 == 0) ? 0 : *quote;
		*bkslh = (*bkslh == 2) ? 0 : *bkslh;
	}
	if (*quote != 0)
	{
		tmp = *line;
		*line = ft_strjoin(tmp, "\n");
		ft_free_ptr(tmp);
	}
}

/*
** pb : no prompt while in quotes && writes itself when ./minishell < script.sh
*/

static void	ft_launch_process(t_sh *sh, t_parse *prompt)
{
	ft_create_pipe(sh);
	prompt->current = sh->cmds->head;
	while (prompt->current)
	{
		ft_signal(SIGINT, OFF);
		ft_signal(SIGQUIT, OFF);
		sh->ret_cmd = ft_parse_cmds((t_cmd *)prompt->current->data, sh);
		prompt->current = prompt->current->next;
	}
}

static void	ft_parse_process(t_sh *sh, t_parse *prompt)
{
	prompt->input = ft_lstnew(sh->line);
	ft_lstadd_back(&sh->begin_input, prompt->input);
	ft_check_line((char**)&prompt->input->content,
						&prompt->quote, &prompt->bkslh);
	prompt->prompt = (prompt->quote == 0) ? PROMPT : QPROMPT;
	if (prompt->quote == 1 || (ft_is_escaped(sh->line, ft_strlen(sh->line))))
		prompt->prompt = QPROMPT;
	if (!prompt->quote && sh->ret_sh
		&& !ft_is_escaped(sh->line, ft_strlen(sh->line))
		&& sh->line[ft_strlen(sh->line) - 1] != '|')
	{
		if (ft_line_to_lst(ft_input_join(sh->begin_input), sh))
			ft_launch_process(sh, prompt);
		sh->line = NULL;
		(sh->begin_input) ? ft_lstclear(&sh->begin_input, &free) : 0;
		ft_reset_sh(sh);
		sh->begin_input = NULL;
	}
	if (sh->line && ft_is_escaped(sh->line, ft_strlen(sh->line)))
		sh->line[ft_strlen(sh->line) - 1] = ' ';
}

void		ft_prompt(t_sh *sh)
{
	t_parse		prompt;

	prompt.quote = 0;
	prompt.bkslh = 0;
	prompt.prompt = PROMPT;
	ft_signal(SIGQUIT, ON);
	ft_signal(SIGINT, ON);
	(sh->fd == 0) ? write(2, prompt.prompt, ft_strlen(prompt.prompt)) : 0;
	while ((sh->ret_sh = get_next_line_multi(sh->fd, &sh->line)) >= 0)
	{
		if (sh->ret_sh == 0 && ft_strlen(sh->line) == 0 && !sh->begin_input)
			ft_exit(NULL, sh);
		prompt.comment = 0;
		while (sh->line[prompt.comment] && ft_isspace(sh->line[prompt.comment]))
			prompt.comment++;
		(sh->line[prompt.comment] == '#') ? ft_safe_free((void**)&sh->line) : 0;
		if (sh->line && sh->line[prompt.comment] != '#')
			ft_parse_process(sh, &prompt);
		ft_signal(SIGQUIT, ON);
		ft_signal(SIGINT, ON);
		if (sh->fd == 0 && sh->ret_sh > 0 && !sh->begin_input)
			write(2, prompt.prompt, ft_strlen(prompt.prompt));
	}
	ft_exit(NULL, sh);
}
