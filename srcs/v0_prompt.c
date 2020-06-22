/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:14:14 by alienard          #+#    #+#             */
/*   Updated: 2020/06/22 16:40:12 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

char	*ft_input_join(t_list **inputs)
{
	char	*tmp;
	char	*tmp_2;
	int		i;
	t_list	*current;

	i = -1;
	tmp = NULL;
	current = *inputs;
	if (current && ft_lstsize(*inputs) > 0)
	{
		while (current)
		{
			tmp_2 = tmp;
			tmp = ft_strjoin(tmp, current->content);
			ft_free_ptr(tmp_2);
			current = current->next;
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
	char		*line;
	// char		**args;
	char		*args;
	int			ret;
	int			i;
	char		*prompt;
	static int	(*builtin_fct[])(char **, t_list **) = {BUILTINS};
	// char		**input;
	int			quote;
	t_sh		sh;
	t_list		*input;
	t_list		**begin;

	*begin = input;
	quote = 0;
	sh = (t_sh) {
			.fd = fd, .line = NULL, .ret_cmd = 0,
			.ret_sh = 0, .blt_fct =  builtin_fct, 
			.cmds = NULL, .env = env};
	// if (!(input = ft_calloc(10 ,sizeof(char *))))
		// return ; // liste chainee malloc de taille 10 pas satisf ?
	ret = 1;
	prompt = PROMPT;
	i = -1;
	while (ret && (write(1,prompt,ft_strlen(prompt)))
		&& (*check = get_next_line(fd, &line)) >= 0)
	{
		// we put line inside a char *[10] -> put it in a chained list instead ?
		input->next = ft_lstnew(line);
		// we check line for quotes
		ft_check_line(&input->next->content, &quote);
		input = input->next;
		// printf("quote : |%d|\n", quote);

		// if there is a quote open, we change the promt
		prompt = (quote == 0) ? PROMPT : QPROMPT;
		// and do not enter the parsing fcts
		if (!quote)
		{
			// if there is no more quote, we rearrange the input
			i = -1;
			// ft_print_double_array(input, "input");

			// split gets 1 cmd per char *
			// args = ft_split_line(input);
			args = ft_input_join(begin);
			ft_line_to_lst(args, &sh);
			// ft_print_double_array(args, "args");
			ft_free_double_array(input);
			// then each cmd is parsed one after the other

			// while (args[++i])
				// ret = ft_parse_line(args[i], env, builtin_fct);
			ft_parse_cmds(&sh);
/*
(void)env;
(void)builtin_fct;
*/

			ft_free_double_array(args);
			if (!(input = ft_calloc(10 ,sizeof(char *))))
				return ; // liste chainee ?
			i = -1;
		}
		ft_free_ptr(line);
		if (*check == 0)
			break ;
	}
	ft_free_double_array(input);
}
