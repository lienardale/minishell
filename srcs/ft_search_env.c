/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 08:49:05 by cdai              #+#    #+#             */
/*   Updated: 2020/09/09 09:57:06 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_search_env(t_list *env, char *arg)
{
	t_env	*result;
	t_env	*env_content;
	t_list	*temp_env;

	temp_env = env;
	if (!(result = ft_separate_key_value(arg)))
		return (NULL);
	while (temp_env)
	{
		env_content = (t_env*)temp_env->content;
		if (ft_strcmp(env_content->key, result->key) == 0)
		{
			ft_free_env_lst(result);
			return (temp_env);
		}
		temp_env = temp_env->next;
	}
	ft_free_env_lst(result);
	return (NULL);
}
