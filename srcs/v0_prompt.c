/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:14:14 by alienard          #+#    #+#             */
/*   Updated: 2020/07/10 15:16:14 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

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
			ft_free_ptr(tmp_2);
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
		if ((*line)[pos] == '\"'&& (*quote == '\"' || *quote == 0)
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
	int			quote;
	t_list		*input;
	t_list		*begin;
	t_dlist		*current;
	int			bkslh;

	begin = NULL;
	quote = 0;
	bkslh = 0;
	while (sh->ret_cmd && (sh->ret_sh = get_next_line_multi(sh->fd, &sh->line)) >= 0)
	{
		input = ft_lstnew(sh->line);
		ft_lstadd_back(&begin, input);
		ft_check_line((char**)&input->content, &quote, &bkslh);
		if (!quote)
		{
			ft_line_to_lst(ft_input_join(begin), sh);
			ft_lstclear(&begin, &free);
			current = sh->cmds->head;
			while (current)
			{
				// if ( ((t_cmd *)current->data)->av[0][0] != '#')
				sh->ret_cmd = ft_parse_cmds((t_cmd *)current->data, sh);
				current = current->next;
			}
			ft_dlst_del(sh->cmds);
		}
		// ft_free_ptr(sh.line);
		if (sh->ret_cmd == 0 || !sh->ret_sh)
			break ;
	}
}

void	ft_ctrl_c(int sig)
{
	(void)sig;
	write(0, "\n", 1);
	write(1, PROMPT, ft_strlen(PROMPT));
}

void	ft_ctrl_backslash(int sig)
{
	(void)sig;
}

void	ft_prompt(t_sh *sh)
{
	char		*prompt;
	int			quote;
	t_list		*input;
	t_list		*begin;
	t_dlist		*current;
	int			bkslh;

	begin = NULL;
	quote = 0;
	bkslh = 0;
	prompt = PROMPT;
signal(SIGQUIT, ft_ctrl_backslash);
signal(SIGINT, ft_ctrl_c);
	while (sh->ret_cmd && (write(1,prompt,ft_strlen(prompt)))
		&& (sh->ret_sh = get_next_line_multi(sh->fd, &sh->line)) >= 0)
	{
		input = ft_lstnew(sh->line);
		ft_lstadd_back(&begin, input);
		ft_check_line((char**)&input->content, &quote, &bkslh);
		prompt = (quote == 0) ? PROMPT : QPROMPT;
		if (!quote)
		{
			ft_line_to_lst(ft_input_join(begin), sh);
			ft_lstclear(&begin, &free);
			current = sh->cmds->head;
			while (current)
			{
				sh->ret_cmd = ft_parse_cmds((t_cmd *)current->data, sh);
				current = current->next;
			}
		if (sh->ret_cmd == 0 || !sh->ret_sh)
			break ;
		}
		// ft_free_ptr(sh.line);
	}
if (sh->ret_sh == 0)
	write(1, "exit\n", 5);
}
