/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_to_lst_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 20:45:51 by cdai              #+#    #+#             */
/*   Updated: 2020/05/31 14:32:18 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

static t_env	*ft_separate_key_value(char *env_str)
{
	t_env	*result;
	int		i;

	i = 0;
	while (env_str[i] && env_str[i] != '=')
		i++;
result = ft_calloc(1, sizeof(result));
	if (!env_str[i])
result->key = ft_strdup(env_str);
	else
	{
result->key = ft_substr(env_str, 0, i);
result->value = ft_substr(env_str, i + 1, ft_strlen(env_str) - i - 1);
	}
	return (result);
}

t_list			*ft_split_to_lst_env(char **env)
{
	t_list	*result;
	int		i;

	i = 0;
	result = NULL;
	while(env[i])
	{
		if (!result)
			result = ft_lstnew(ft_separate_key_value(env[i]));
		else
			ft_lstadd_back(&result, ft_lstnew(ft_separate_key_value(env[i])));
		i++;
	}
	return (result);
}
