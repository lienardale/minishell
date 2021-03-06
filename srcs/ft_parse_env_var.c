/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:16:34 by cdai              #+#    #+#             */
/*   Updated: 2020/09/17 18:21:11 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_get_env_var_length(char *line, int *i, t_sh *sh)
{
	int		res;
	int		j;
	char	*temp;
	t_list	*temp_env;

	res = 0;
	j = (*i) + 1;
	if (line[++(*i)] == '?')
		return (ft_itoa_count(sh->ret_cmd));
	while ((line[*i]) && (ft_isalpha(line[*i]) || ft_isinquotes(line, *i)
		|| ft_is_escaped(line, *i)))
		(*i)++;
	if ((temp = ft_substr(line, j, *i - j)) != NULL)
	{
		temp_env = ft_search_env(*(sh->env), temp);
		if (temp_env)
		{
			res = ft_strlen(((t_env *)(temp_env->content))->value);
			free(temp);
			return (res);
		}
		free(temp);
		return (0);
	}
	return (-1);
}

static int	ft_parse_env_var_count(char *line, t_sh *sh)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (line[i])
	{
		if (line[i] == '$' && !ft_isinsquotes(line, i)
			&& !ft_is_escaped(line, i))
			result += ft_get_env_var_length(line, &i, sh);
		else
		{
			i++;
			result++;
		}
	}
	return (result);
}

static int	ft_fullfill_env_var_cat(char **result, int len,
									char **temp, t_list **temp_env)
{
	ft_strlcat(*result, ((t_env *)((*temp_env)->content))->value, len);
	ft_safe_free((void**)temp);
	return (ft_strlen(((t_env *)((*temp_env)->content))->value));
}

static int	ft_fullfill_env_var(char *line, char *result, int **i, t_sh *sh)
{
	int		j;
	int		len;
	char	*temp;
	t_list	*temp_env;

	j = (*i[0]) + 1;
	len = (*i[1]) + 1;
	if (line[++(*i[0])] == '?' && ((*i[0])++))
	{
		temp = ft_itoa(sh->ret_cmd);
		ft_strlcat(result, temp, len);
		ft_safe_free((void**)&temp);
		return (ft_itoa_count(sh->ret_cmd));
	}
	while ((line[*i[0]]) && (ft_isalpha(line[*i[0]])
		|| ft_isinquotes(line, *i[0]) || ft_is_escaped(line, *i[0])))
		(*i[0])++;
	if ((temp = ft_substr(line, j, *i[0] - j)) != NULL)
	{
		if ((temp_env = ft_search_env(*(sh->env), temp)) != NULL)
			return (ft_fullfill_env_var_cat(&result, len, &temp, &temp_env));
		ft_safe_free((void**)&temp);
		return (0);
	}
	return (-1);
}

char		*ft_parse_env_var(char *line, t_sh *sh)
{
	char	*result;
	int		i[2];
	int		j;

	i[0] = 0;
	j = 0;
	i[1] = ft_parse_env_var_count(line, sh);
	result = ft_calloc(1, i[1] + 1);
	while (line[i[0]])
	{
		if (line[i[0]] == '$' && !ft_isinsquotes(line, i[0])
			&& !ft_is_escaped(line, i[0]))
			j += ft_fullfill_env_var(line, result, (int**)&i, sh);
		else
		{
			result[j] = line[i[0]];
			i[0]++;
			j++;
		}
	}
	return (sh->line);
}
