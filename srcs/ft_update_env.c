/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 09:20:04 by cdai              #+#    #+#             */
/*   Updated: 2020/09/02 16:20:01 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

t_list *ft_update_env(t_list *env, t_env *data)
{
	t_list	*temp_env;
	t_list	*to_add;

	temp_env = ft_search_env(env, data->key);
	if (temp_env)
	{
		free(((t_env*)temp_env->content)->value);
		((t_env*)temp_env->content)->value = data->value;
		free(data->key);
		free(data);
	}
	else
	{
// attention malloc
		if (!(to_add = ft_lstnew(data)))
			return (NULL);
		ft_lstadd_back(&env, to_add);	
	}
	return (env);
}
