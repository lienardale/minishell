/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_separate_key_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:19:23 by cdai              #+#    #+#             */
/*   Updated: 2020/06/04 18:20:03 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

t_env	*ft_separate_key_value(char *env_str)
{
	t_env	*result;
	int		i;

	i = 0;
	while (env_str[i] && env_str[i] != '=')
		i++;
	result = ft_calloc(1, sizeof(*result));
	if (!env_str[i])
		result->key = ft_strdup(env_str);
	else
	{
		result->key = ft_substr(env_str, 0, i);
		result->value = ft_substr(env_str, i + 1, ft_strlen(env_str) - i - 1);
	}
	return (result);
}
