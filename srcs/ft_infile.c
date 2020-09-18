/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_infile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 11:45:16 by alienard          #+#    #+#             */
/*   Updated: 2020/09/18 12:31:02 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_parse_process(t_sh *sh, t_parse *file)
{
	file->input = ft_lstnew(sh->line);
	ft_lstadd_back(&sh->begin_input, file->input);
	ft_check_line((char**)&file->input->content, &file->quote, &file->bkslh);
	if (!file->quote && !ft_is_escaped(sh->line, ft_strlen(sh->line))
		&& sh->line[ft_strlen(sh->line) - 1] != '|')
	{
		if ((file->error =
			ft_line_to_lst(ft_input_join(sh->begin_input), sh)))
		{
			ft_create_pipe(sh);
			file->current = sh->cmds->head;
			while (file->current)
			{
				sh->ret_cmd = ft_parse_cmds((t_cmd *)file->current->data, sh);
				file->current = file->current->next;
			}
		}
		sh->line = NULL;
		(sh->begin_input) ? ft_lstclear(&sh->begin_input, &free) : 0;
		ft_reset_sh(sh);
		sh->begin_input = NULL;
		if (!file->error)
			return (1);
	}
	return (0);
}

void		ft_infile(t_sh *sh)
{
	t_parse	file;

	file.quote = 0;
	file.bkslh = 0;
	while ((sh->ret_sh = get_next_line_multi(sh->fd, &sh->line)) >= 0)
	{
		if (sh->ret_sh == 0 && ft_strlen(sh->line) == 0 && !sh->begin_input)
			ft_exit(NULL, sh);
		file.comment = 0;
		sh->nbline++;
		while (sh->line[file.comment] && ft_isspace(sh->line[file.comment]))
			file.comment++;
		if (sh->line[file.comment] == '#')
			ft_safe_free((void**)&sh->line);
		if (sh->line && sh->line[file.comment] != '#')
		{
			if (ft_parse_process(sh, &file))
				break ;
			if (sh->line && ft_is_escaped(sh->line, ft_strlen(sh->line)))
				sh->line[ft_strlen(sh->line) - 1] = ' ';
		}
	}
	ft_exit(NULL, sh);
}
