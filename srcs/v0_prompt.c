/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:14:14 by alienard          #+#    #+#             */
/*   Updated: 2020/06/25 16:07:32 by alienard         ###   ########.fr       */
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

void	ft_check_line(char **line, int *quote)
{
	int		pos;
	int		nbquote;
	char	*tmp;

	pos = -1;
	nbquote = (*quote == 0) ? 0 : 1;
	while ((*line)[++pos])
	{
		if ((*line)[pos] == '\'' && (*quote == '\'' || *quote == 0))
		{
			nbquote++;
			*quote = '\'';
		}
		if ((*line)[pos] == '\"'&& (*quote == '\"' || *quote == 0))
		{
			nbquote++;
			*quote = '\"';
		}
		if (nbquote % 2 == 0)
			*quote = 0;
	}
	if (*quote != 0)
	{
		tmp = *line;
		*line = ft_strjoin(tmp, "\n");
		ft_free_ptr(tmp);
	}
}

void	ft_prompt(int *check, int fd, t_list **env)
{
	char		*args;
	char		*prompt;
	static int	(*builtin_fct[])(char **, t_list **) = {BUILTINS};
	int			quote;
	t_sh		sh;
	t_list		*input;
	t_list		*begin;
	t_dlist		*current;

	begin = NULL;
	quote = 0;
	sh = (t_sh) {
			.fd = fd, .line = NULL, .ret_cmd = 1,
			.ret_sh = 0, .blt_fct = builtin_fct, 
			.cmds = NULL, .env = env};
	prompt = PROMPT;
	while (sh.ret_cmd && (write(1,prompt,ft_strlen(prompt)))
		&& (*check = get_next_line(fd, &sh.line)) >= 0)
	{
		input = ft_lstnew(sh.line);
		ft_lstadd_back(&begin, input);
		ft_check_line((char**)&input->content, &quote);
		prompt = (quote == 0) ? PROMPT : QPROMPT;
		if (!quote)
		{
			args = ft_input_join(begin);
			// ft_init_dlst(&sh.cmds);
			ft_line_to_lst(args, &sh);
			// ft_print_dlst(sh.cmds->head, "cmds-out:");
			ft_lstclear(&begin, &free);
			current = sh.cmds->head;
			// ft_print_dlst(current, "curr:");
			// printf("%s\n", sh.cmds->head->data->cmd);
			while (current)
			{
				sh.ret_cmd = ft_parse_cmds((t_cmd *)current->data, &sh);
				current = current->next;
			}
			ft_free_ptr(args);
		}
		// ft_free_ptr(sh.line);
		if (*check == 0)
			break ;
	}
}
