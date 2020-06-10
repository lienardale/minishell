/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:14:14 by alienard          #+#    #+#             */
/*   Updated: 2020/06/10 12:12:56 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

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
		ft_printf("%s[%d]:|%s|\n", name, i, str[i]);
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

void	ft_prompt(int *check, int fd, char **env)
{
	char		*line;
	char		**args;
	int			ret;
	int			i;
	char		*prompt;
	static int	(*builtin_fct[])(char **, char **) = {BUILTINS};
	char		**input;
	int			quote;

	quote = 0;
	if (!(input = ft_calloc(10 ,sizeof(char *))))
		return ; // liste chainee malloc de taille 10 pas satisf ?
	ret = 1;
	prompt = PROMPT;
	i = -1;
	while (ret && (write(1,prompt,ft_strlen(prompt)))
		&& (*check = get_next_line(fd, &line)) >= 0)
	{
		// we put line inside a char *[10] -> put it in a chained list instead ?
		input[++i] = ft_strdup(line);
		// we check line for quotes
		ft_check_line(&input[i], &quote);
		// if there is a quote open, we change the promt
		prompt = (quote == 0) ? PROMPT : QPROMPT;
		// and do not enter the parsing fcts
		if (!quote)
		{
			// if there is no more quote, we rearrange the input
			i = -1;
			// split gets 1 cmd per char *
			args = ft_split_line(input);
			ft_free_double_array(input);
			// then each cmd is parsed one after the other
			ret = ft_pipe_split(args, env, builtin_fct);
			if (!(input = ft_calloc(10 ,sizeof(char *))))
				return ; // liste chainee ?
		}
		ft_free_ptr(line);
		if (*check == 0)
			break ;
	}
	ft_free_double_array(input);
}
