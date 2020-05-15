/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:14:14 by alienard          #+#    #+#             */
/*   Updated: 2020/05/15 14:55:43 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

void	ft_check_line(char *line, int *quote)
{
	int		pos;
	int		nbquote;

	pos = -1;
	nbquote = (*quote == 0) ? 0 : 1;
	while (line[++pos])
	{
		if (line[pos] == '\'' && (*quote == '\'' || *quote == 0))
		{
			nbquote++;
			*quote = '\'';
		}
		if (line[pos] == '\"'&& (*quote == '\"' || *quote == 0))
		{
			nbquote++;
			*quote = '\"';
		}
	}
	if (nbquote == 2)
		*quote = 0;
}

void	ft_free_double_array(char **str)
{
	int		i;

	i = -1;
	while (str[++i])
		(str[i]) ? ft_free_ptr(str[i]) : 0;
	(str) ? ft_free_ptr(str) : 0;
}

void	ft_print_double_array(char **str, char *name)
{
	int		i;

	i = -1;
	while (str[++i])
		printf("%s[%d]:|%s|\n", name, i, str[i]);
}

void	ft_prompt(int *check, int fd, char **env)
{
	char		*line;
	char		**args;
	int			ret;
	int			i;
	char		*prompt;
	static int	(*builtin_fct[])(char **) = {BUILTINS};
	char		**input;
	int			quote;

	quote = 0;
	if (!(input = ft_calloc(10 ,sizeof(char *))))
		return ; // liste chainee malloc de taille 10 pas satisf ?
	ret = 1;
	prompt = PROMPT;
	i = -1;
	while (ret && (write(1,prompt,ft_strlen(prompt))) && (*check = get_next_line(fd, &line)) >= 0)
	{
		input[++i] = ft_strdup(line); //strdup_free
		// input = ft_realloc(input, i);
		ft_check_line(line, &quote); //ternaire ?
		prompt = (quote == 0) ? PROMPT : QPROMPT;
		if (!quote)
		{
			i = -1;
			ft_print_double_array(input, "input");
			args = ft_split_line(input);
			ft_print_double_array(args, "args");
			while (args[++i])
				ret = ft_parse_line(args[i], env, builtin_fct);
			ft_free_double_array(input);
			ft_free_double_array(args);
			if (!(input = ft_calloc(10 ,sizeof(char *))))
				return ; // liste chainee ?
		}
		ft_free_ptr(line);
		if (*check == 0)
			break ;
	}
}
