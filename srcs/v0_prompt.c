/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:14:14 by alienard          #+#    #+#             */
/*   Updated: 2020/09/09 14:10:54 by cdai             ###   ########.fr       */
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
//			ft_free_ptr(tmp_2);
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
	int			comment;
	int			quote;
	int			bkslh;
	t_list		*input;
	t_list		*begin;
	t_dlist		*current;

	begin = NULL;
	quote = 0;
	bkslh = 0;
	while ((sh->ret_sh = get_next_line(sh->fd, &sh->line)) >= 0)
	{
//printf("ici\n");
		if (sh->ret_sh == 0 && ft_strlen(sh->line) == 0 && !begin)
			ft_exit(NULL, sh);
		comment = 0;
		sh->nbline++;
		while (sh->line[comment] && ft_isspace(sh->line[comment]))
			comment++;
		if (sh->line[comment] != '#') // so that we can comment lines
		{
			input = ft_lstnew(sh->line);
			ft_lstadd_back(&begin, input);;
			ft_check_line((char**)&input->content, &quote, &bkslh);
			if (!quote && !ft_is_escaped(sh->line, ft_strlen(sh->line)))
			{
				if (!ft_line_to_lst(ft_input_join(begin), sh))
					break ;
//				ft_lstclear(&begin, &free);
				ft_create_pipe(sh);
				current = sh->cmds->head;
				while (current)
				{
					sh->ret_cmd = ft_parse_cmds((t_cmd *)current->data, sh);
					current = current->next;
				}
//				ft_dlst_del(sh->cmds);
			}
			if (ft_is_escaped(sh->line, ft_strlen(sh->line)))
				sh->line[ft_strlen(sh->line) - 1] = ' ';
		}
		// ft_free_ptr(sh.line);
		// if (!sh->ret_sh)
		// 	break ;
	}
}

void	ft_prompt(t_sh *sh)
{
	char		*prompt;
	int			quote;
	int			comment;
	t_list		*input;
	t_list		*begin;
	t_dlist		*current;
	int			bkslh;

	begin = NULL;
	quote = 0;
	bkslh = 0;
	prompt = PROMPT;
	ft_signal(SIGQUIT, ON);
	ft_signal(SIGINT, ON);
	if (sh->fd == 0)
			write(2,prompt,ft_strlen(prompt));
	while (//sh->ret_cmd /*&& (write(1,prompt,ft_strlen(prompt)))*/ // /!\ pb, when several lines are ctrl -v into stdin, prompt writes itself several times at the end && 
		(sh->ret_sh = get_next_line(sh->fd, &sh->line)) >= 0)
	{
		if (sh->ret_sh == 0 && ft_strlen(sh->line) == 0 && !begin)
		{
			free(sh->line);
			ft_exit(NULL, sh);
		}
			//	write(1, "exit\n", 5);
		comment = 0;
		while (sh->line[comment] && ft_isspace(sh->line[comment]))
			comment++;
		if (sh->line[comment] != '#') // so that we can comment lines -> /!\ need do handle "echo coucou #; ls"
		{
			input = ft_lstnew(sh->line);
			ft_lstadd_back(&begin, input);
			ft_check_line((char**)&input->content, &quote, &bkslh);
			prompt = (quote == 0) ? PROMPT : QPROMPT;
			// printf("|%s|\n", &sh->line[ft_strlen(sh->line) - 1]);
			if (quote == 1 || (ft_is_escaped(sh->line, ft_strlen(sh->line))))
				prompt = QPROMPT;
			// sh->line = NULL;
			if (!quote && sh->ret_sh && !ft_is_escaped(sh->line, ft_strlen(sh->line)))
			{
				if (!ft_line_to_lst(ft_input_join(begin), sh))
{
					ft_reset_sh(sh);
					return (ft_prompt(sh));
}
				// ft_line_to_lst(ft_input_join(begin), sh);
				ft_lstclear(&begin, &free);
				ft_create_pipe(sh);
				current = sh->cmds->head;
				while (current)
				{
					ft_signal(SIGINT, OFF);
					ft_signal(SIGQUIT, OFF);
					sh->ret_cmd = ft_parse_cmds((t_cmd *)current->data, sh);
					current = current->next;
				}
//				free(sh->cmds->head->data->cmd);
//				ft_dlst_del(sh->cmds);
				begin = NULL;
				ft_reset_sh(sh);
			}
			if (ft_is_escaped(sh->line, ft_strlen(sh->line)))
				sh->line[ft_strlen(sh->line) - 1] = ' ';
		}
		ft_signal(SIGQUIT, ON);
		ft_signal(SIGINT, ON);
		/*
		if (sh->ret_cmd == 0 || !sh->ret_sh)
			break ;
		 * */

		// pb : no prompt while in quotes -> needs fixing
		if (sh->fd == 0 && sh->ret_sh > 0 && (!begin/* || quote*/))
			write(2, prompt, ft_strlen(prompt));
		
		// ft_free_ptr(sh.line);
	}
}
