/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 19:43:17 by cdai              #+#    #+#             */
/*   Updated: 2020/05/18 20:31:58 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

static char	*ft_increment_shlvl(char *env_shlvl)
{
	int		shlvl;
	char	*temp;
	char	*result;
	int		result_len;

	shlvl = ft_atoi(env_shlvl + 6);
	temp = ft_itoa(++shlvl);
	result_len = 7 + ft_strlen(temp);
	result = ft_calloc(result_len, sizeof(char));
	ft_strlcat(result, "SHLVL=", result_len);
	ft_strlcat(result, temp, result_len);
	free(temp);
	return (result);
}

char	**ft_start_minishell(char **env)
{
	int		i;
	char	*temp;

	i = 0;
	if (!(env = ft_splitcpy(env)))
		return (NULL);
	while (env[i])
	{
		if (!ft_strncmp(env[i], "SHLVL=", 6))
		{
			temp = env[i];
			if (!(env[i] = ft_increment_shlvl(env[i])))
				return (ft_free_split(env));
			free(temp);
		}
		// printf("start_minishell/env[%d]: %s\n", i, env[i]);
		i++;
	}
	return (env);
}
