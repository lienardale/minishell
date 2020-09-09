/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 09:20:04 by cdai              #+#    #+#             */
/*   Updated: 2020/09/09 11:29:25 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *ft_update_env(t_list *env, t_env *data, bool add)
{
	t_list	*temp_env;
	t_list	*to_add;

	temp_env = ft_search_env(env, data->key);
	// printf("key:%s\nvalue:%s\n", data->key, data->value);
	if (temp_env && data->value)
	{
		if (add == false)
			((t_env*)temp_env->content)->value = data->value;
		else
			((t_env*)temp_env->content)->value = ft_strjoin(((t_env*)temp_env->content)->value, data->value);
		free(data->key);
		free(data);
	}
	else if (!temp_env)
	{
// attention malloc
		if (!(to_add = ft_lstnew(data)))
			return (NULL);
		ft_lstadd_back(&env, to_add);
	}
	return (env);
}
