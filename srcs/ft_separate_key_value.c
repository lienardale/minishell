/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_separate_key_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:19:23 by cdai              #+#    #+#             */
/*   Updated: 2020/09/16 10:26:39 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_separate_key_value(char *env_str, bool *add)
{
	t_env	*result;
	int		i;

	i = 0;
	while (env_str[i] && env_str[i] != '=' && env_str[i] != '+')
		i++;
	if (env_str[i] == '+' && env_str[i + 1] && env_str[i + 1] == '=' && (i++))
		(*add) = true;
	if (!(result = ft_calloc(1, sizeof(*result))))
		return (NULL);
	if (!env_str[i])
	{
		if (!(result->key = ft_strdup(env_str)))
		{
			// ft_free_env_lst(result);
			return (NULL);
		}
	}
	else
	{
		if (result->key)
			free(result->key);
		if (!(result->key = ft_substr(env_str, 0, i)))
			return (NULL);
		if (result->value)
			free(result->value);
		if (!(result->value = ft_substr(env_str, i + 1, ft_strlen(env_str) - i - 1)))
			return (NULL);
	}
	// else if (!(result->key = ft_substr(env_str, 0, i)) ||
	// (!(result->value = ft_substr(env_str, i + 1, ft_strlen(env_str) - i - 1))))
	// {
	// 	// ft_free_env_lst(result);
	// 	return (NULL);
	// }
	return (result);
}
