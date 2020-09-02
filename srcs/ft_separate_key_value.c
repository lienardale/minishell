/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_separate_key_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:19:23 by cdai              #+#    #+#             */
/*   Updated: 2020/09/02 18:05:56 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_separate_key_value(char *env_str)
{
	t_env	*result;
	int		i;

	i = 0;
	while (env_str[i] && env_str[i] != '=')
		i++;
	if (!(result = ft_calloc(1, sizeof(*result))))
		return (NULL);
	if (!env_str[i])
	{
		if (!(result->key = ft_strdup(env_str)))
		{
			ft_free_env_lst(result);
			return (NULL);
		}
	}
	else if (!(result->key = ft_substr(env_str, 0, i)) ||
	(!(result->value = ft_substr(env_str, i + 1, ft_strlen(env_str) - i - 1))))
	{
		ft_free_env_lst(result);
		return (NULL);
	}
	return (result);
}
