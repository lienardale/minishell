/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:16:34 by cdai              #+#    #+#             */
/*   Updated: 2020/07/23 17:12:46 by cdai             ###   ########.fr       */
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
// juste passer le premier charactere qui doit etre un $
	(*i)++;
	j = *i;
	if (sh->line[*i] == '?')
		return (ft_itoa_count(sh->ret_cmd));
	while ((sh->line[*i]) && ft_isalpha(sh->line[*i]))
		(*i)++;
	temp = ft_substr(sh->line, j, *i - j);
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
// attention au erreur de malloc
			result += ft_get_env_var_length(sh, &i);
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

static int	ft_fullfill_env_var(t_sh *sh, char *result, int len, int *i)
{
	int		j;
	char	*temp;
	t_list	*temp_env;

// juste passer le premier charactere qui doit etre un $
	(*i)++;
	j = *i;
	if (sh->line[*i] == '?')
	{
		(*i)++;
// attention malloc error
		temp = ft_itoa(sh->ret_cmd);
		ft_strlcat(result, temp, len);
		free(temp);
		return (ft_itoa_count(sh->ret_cmd));
	}
	while ((sh->line[*i]) && ft_isalpha(sh->line[*i]))
		(*i)++;
	temp = ft_substr(sh->line, j, *i - j);
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
// attention au erreur de malloc
	while (sh->line[i])
	{	
		if (sh->line[i] == '$')
			j += ft_fullfill_env_var(sh, result, len + 1, &i);
// attention au erreur de malloc
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
