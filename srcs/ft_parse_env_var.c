/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:16:34 by cdai              #+#    #+#             */
/*   Updated: 2020/07/20 12:35:34 by cdai             ###   ########.fr       */
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
	(*i)++;
	j = *i;
	while ((sh->line[*i]) && (sh->line[*i] != ' ' && sh->line[*i] != '"'))
		(*i)++;
temp = ft_substr(sh->line, j, *i - j);
//printf("%s\n", temp);
temp_env = ft_search_env(*(sh->env), temp);
//printf("%s\n", ((t_env *)(temp_env->content))->value);
res = ft_strlen(((t_env *)(temp_env->content))->value);
free(temp);
return (res);
}

static int	ft_parse_env_var_count(t_sh *sh)
{
	int	i;
	int	is_in_simple_quote;
	int	result;

	i = 0;
	is_in_simple_quote = 0;
	result = 0;
	while (sh->line[i])
	{
		if (sh->line[i] == '\'')
			is_in_simple_quote = is_in_simple_quote ? 0 : 1;
		if (sh->line[i] == '$' && !is_in_simple_quote)
			result += ft_get_env_var_length(sh, &i);
		else
		{
			i++;
			result++;
		}
	}
	return (result);
}

static int	ft_fullfill_env_var(t_sh *sh, char *result, int len, int *i)
{
	(void)result;
	(void)len;
	int		j;
	char	*temp;
	t_list	*temp_env;

	(*i)++;
	j = *i;
	while ((sh->line[*i]) && (sh->line[*i] != ' ' && sh->line[*i] != '"'))
		(*i)++;
temp = ft_substr(sh->line, j, *i - j);
//printf("%s\n", temp);
temp_env = ft_search_env(*(sh->env), temp);
printf("%s\n", ((t_env *)(temp_env->content))->value);

	ft_strlcat(result, ((t_env *)(temp_env->content))->value, len);
free(temp);

//	return 0;
	return (ft_strlen(((t_env *)(temp_env->content))->value));
}

char		*ft_parse_env_var(t_sh *sh)
{
	char	*result;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = ft_parse_env_var_count(sh);
//printf("%d\n", len);
	result = ft_calloc(1, len + 1);
	while (sh->line[i])
	{	
		if (sh->line[i] == '$')
			j += ft_fullfill_env_var(sh, result, len + 1, &i);
		else
		{
		result[j] = sh->line[i];
			i++;
			j++;
		}
	}
	free(sh->line);
	return (result);
//	return (sh->line);
}
