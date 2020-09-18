/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_separate_key_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:19:23 by cdai              #+#    #+#             */
/*   Updated: 2020/09/18 13:07:08 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_separate_key_value(char *str, bool *add)
{
	t_env	*result;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	if (str[i] == '+' && str[i + 1] && str[i + 1] == '=' && (i++))
		(*add) = true;
	if (!(result = ft_calloc(1, sizeof(*result))))
		return (NULL);
	if (!str[i])
	{
		if (!(result->key = ft_strdup(str)))
			return (NULL);
	}
	else
	{
		ft_safe_free((void**)result->key);
		if (!(result->key = ft_substr(str, 0, i)))
			return (NULL);
		ft_safe_free((void**)result->value);
		if (!(result->value = ft_substr(str, i + 1, ft_strlen(str) - i - 1)))
			return (NULL);
	}
	return (result);
}
