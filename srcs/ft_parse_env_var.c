/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:16:34 by cdai              #+#    #+#             */
/*   Updated: 2020/08/05 12:24:33 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

static int	ft_get_env_var_length(char *line, int *i, t_sh *sh)
{
	int		res;
	int		j;
	char	*temp;
	t_list	*temp_env;

	res = 0;
// juste passer le premier charactere qui doit etre un $
	(*i)++;
	j = *i;
	if (line[*i] == '?')
		return (ft_itoa_count(sh->ret_cmd));
	while ((line[*i]) && (ft_isalpha(line[*i]) || ft_isinquotes(line, *i) || ft_is_escaped(line, *i)))
		(*i)++;
	temp = ft_substr(line, j, *i - j);
	if (temp)
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
	// int	is_in_simple_quote;
	int	result;

	i = 0;
	// is_in_simple_quote = 0;
	result = 0;
	while (line[i])
	{
		// if (line[i] == '\'')
		// 	is_in_simple_quote = is_in_simple_quote ? 0 : 1;
		if (line[i] == '$' && !ft_isinsquotes(line, i) && !ft_is_escaped(line, i))
// attention au erreur de malloc
			result += ft_get_env_var_length(line, &i, sh);
		else
		{
			i++;
			result++;
		}
	}
// je ne suis pas sur pour ca
//	if (!is_in_simple_quote)
//		return (result);
//	return (0);
	return (result);
}

static int	ft_fullfill_env_var(char *line, char *result, int len, int *i, t_sh *sh)
{
	int		j;
	char	*temp;
	t_list	*temp_env;

// juste passer le premier charactere qui doit etre un $
	(*i)++;
	j = *i;
	if (line[*i] == '?')
	{
		(*i)++;
// attention malloc error
		temp = ft_itoa(sh->ret_cmd);
		ft_strlcat(result, temp, len);
		free(temp);
		return (ft_itoa_count(sh->ret_cmd));
	}
	while ((line[*i]) && (ft_isalpha(line[*i]) || ft_isinquotes(line, *i) || ft_is_escaped(line, *i)))
		(*i)++;
	temp = ft_substr(line, j, *i - j);
	if (temp)
	{
		temp_env = ft_search_env(*(sh->env), temp);
		if (temp_env)
		{
			ft_strlcat(result, ((t_env *)(temp_env->content))->value, len);
			free(temp);
			return (ft_strlen(((t_env *)(temp_env->content))->value));
		}
		free(temp);
		return (0);
	}
	return (-1);
}

char		*ft_parse_env_var(char *line, t_sh *sh)
{
	char	*result;
	int		i;
	int		j;
	int		len;
	// int		is_in_simple_quote;

	i = 0;
	j = 0;
	// is_in_simple_quote = 0;
	len = ft_parse_env_var_count(line, sh);
	//printf("%d\n", len);
	result = ft_calloc(1, len + 1);
// attention au erreur de malloc
	while (line[i])
	{	
// attention au erreur de malloc
		if (line[i] == '$' && !ft_isinsquotes(line, i) && !ft_is_escaped(line, i))
			j += ft_fullfill_env_var(line, result, len + 1, &i, sh);
		else
		{
			result[j] = line[i];
			i++;
			j++;
		}
	}
//	free(sh->line);
	// return (result);
	return (sh->line);
}
