/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:16:34 by cdai              #+#    #+#             */
/*   Updated: 2020/07/16 16:46:54 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

static int	ft_get_env_var_length(t_sh *sh, int *i)
{
	int		res;
	int		j;
	char	*temp;
	t_list	*temp_env;

	res = 0;
	i++;
	j = *i;
	while (sh->line[*i] && (sh->line[*i] != ' ' || sh->line[*i] == '"')
		*i++;
temp = ft_substr(sh->line + j, j, *i - j);
temp_env = ft_search_env(sh->env, temp);
res = ft_strlen(temp_env->value);
free(temp);
ft_free_env_lst(temp_env);
	return (res);
}

static int	ft_parse_env_var_count(t_sh *sh)
{
	int	i;
	int	is_in_simple_quote;

	i = 0;
	is_in_simple_quote = 0;
	while (sh->line[i])
	{
		if (sh->line[i] == ''')
			is_in_simple_quote = is_in_simple_quote ? 0 : 1;
		if (sh->line[i] == '$' && !is_in_simple_quote)
			result =+ ft_parse_env_var_count(sh->line, &i);
		else
		{
			i++;
			result++;
		}
	}
	return (result);
}

char		*ft_parse_env_var(t_sh *sh)
{
	char	*result;
	int		i;
	int		len;

	i = 0;
	len = ft_parse_env_var_count(sh);
	result = ft_calloc(1, len + 1);

	return (result);
}
