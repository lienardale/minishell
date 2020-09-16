/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:14:14 by alienard          #+#    #+#             */
/*   Updated: 2020/09/16 12:55:20 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_input_join(t_list *inputs)
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

void	ft_check_line(char **line, int *quote, int *bkslh)
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
			&& *bkslh == 0)
		{
			nbquote++;
			*quote = '\'';
		}
		if ((*line)[pos] == '\"' && (*quote == '\"' || *quote == 0)
			&& *bkslh == 0)
		{
			nbquote++;
			*quote = '\"';
		}
		if (nbquote % 2 == 0)
			*quote = 0;
		*bkslh = (*bkslh == 2) ? 0 : *bkslh;
	}
	if (*quote != 0)
	{
		tmp = *line;
		*line = ft_strjoin(tmp, "\n");
		ft_free_ptr(tmp);
	}
}

void	ft_infile(t_sh *sh)
{
	int			comment;
	int			quote;
	int			bkslh;
	int			error;
	t_list		*input;
	t_dlist		*current;

	quote = 0;
	bkslh = 0;
	while ((sh->ret_sh = get_next_line_multi(sh->fd, &sh->line)) >= 0)
	{
		if (sh->ret_sh == 0 && ft_strlen(sh->line) == 0 && !sh->begin_input)
			ft_exit(NULL, sh);
		comment = 0;
		sh->nbline++;
		while (sh->line[comment] && ft_isspace(sh->line[comment]))
			comment++;
		if (sh->line[comment] == '#')
		{
			free(sh->line);
			sh->line = NULL;
		}
		if (sh->line && sh->line[comment] != '#')
		{
			input = ft_lstnew(sh->line);
			ft_lstadd_back(&sh->begin_input, input);
			ft_check_line((char**)&input->content, &quote, &bkslh);
			if (!quote && !ft_is_escaped(sh->line, ft_strlen(sh->line))
				&& sh->line[ft_strlen(sh->line) - 1] != '|')
			{
				if ((error = ft_line_to_lst(ft_input_join(sh->begin_input), sh)))
				{
					ft_create_pipe(sh);
					current = sh->cmds->head;
					while (current)
					{
						sh->ret_cmd = ft_parse_cmds((t_cmd *)current->data, sh);
						current = current->next;
					}
				}
				sh->line = NULL;
				ft_lstclear(&sh->begin_input, &free);
				ft_reset_sh(sh);
				sh->begin_input = NULL;
				if (!error)
					break ;
			}
			if (sh->line && ft_is_escaped(sh->line, ft_strlen(sh->line)))
				sh->line[ft_strlen(sh->line) - 1] = ' ';
		}
	}
	ft_exit(NULL, sh);
}

/*
** pb : no prompt while in quotes && writes itself when ./minishell < script.sh
*/

void	ft_prompt(t_sh *sh)
{
	char		*prompt;
	int			quote;
	int			comment;
	t_list		*input;
	t_dlist		*current;
	int			bkslh;

	quote = 0;
	bkslh = 0;
	prompt = PROMPT;
	ft_signal(SIGQUIT, ON);
	ft_signal(SIGINT, ON);
	if (sh->fd == 0)
		write(2, prompt, ft_strlen(prompt));
	while ((sh->ret_sh = get_next_line_multi(sh->fd, &sh->line)) >= 0)
	{
		if (sh->ret_sh == 0 && ft_strlen(sh->line) == 0 && !sh->begin_input)
		{
			ft_exit(NULL, sh);
		}
		comment = 0;
		while (sh->line[comment] && ft_isspace(sh->line[comment]))
			comment++;
		if (sh->line[comment] == '#')
		{
			free(sh->line);
			sh->line = NULL;
		}
		if (sh->line && sh->line[comment] != '#')
		{
			input = ft_lstnew(sh->line);
			ft_lstadd_back(&sh->begin_input, input);
			ft_check_line((char**)&input->content, &quote, &bkslh);
			prompt = (quote == 0) ? PROMPT : QPROMPT;
			if (quote == 1 || (ft_is_escaped(sh->line, ft_strlen(sh->line))))
				prompt = QPROMPT;
			if (!quote && sh->ret_sh
				&& !ft_is_escaped(sh->line, ft_strlen(sh->line))
				&& sh->line[ft_strlen(sh->line) - 1] != '|')
			{
				if (ft_line_to_lst(ft_input_join(sh->begin_input), sh))
				{
					ft_create_pipe(sh);
					current = sh->cmds->head;
					while (current)
					{
						ft_signal(SIGINT, OFF);
						ft_signal(SIGQUIT, OFF);
						sh->ret_cmd = ft_parse_cmds((t_cmd *)current->data, sh);
						current = current->next;
					}
				}
				sh->line = NULL;
				if (sh->begin_input)
					ft_lstclear(&sh->begin_input, &free);
				ft_reset_sh(sh);
				sh->begin_input = NULL;
					// return (ft_prompt(sh));
			}
			if (sh->line && ft_is_escaped(sh->line, ft_strlen(sh->line)))
				sh->line[ft_strlen(sh->line) - 1] = ' ';
		}
		ft_signal(SIGQUIT, ON);
		ft_signal(SIGINT, ON);
		if (sh->fd == 0 && sh->ret_sh > 0 && !sh->begin_input)
			write(2, prompt, ft_strlen(prompt));
	}
	ft_exit(NULL, sh);
}
