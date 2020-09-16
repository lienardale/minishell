/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 09:09:58 by cdai              #+#    #+#             */
/*   Updated: 2020/09/16 18:00:20 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_new_env_var(char *key, char *value)
{
	t_env	*result;

	if (!(result = ft_calloc(1, sizeof(*result))))
		return (NULL);
	else if (!(result->key = ft_strdup(key)))
	{
		ft_free_env_lst(result);
		return (NULL);
	}
	else if (!(result->value = ft_strdup(value)))
	{
		ft_free_env_lst(result);
		return (NULL);
	}
	return (result);
}
