/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 09:20:04 by cdai              #+#    #+#             */
/*   Updated: 2020/09/18 14:17:12 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_iftempenv(char **old_value, t_list **temp_env,
							t_env **data, bool add)
{
	*old_value = ((t_env*)(*temp_env)->content)->value;
	if (((t_env*)(*temp_env)->content)->value && add == false)
		free(*old_value);
	if (add == false)
		((t_env*)(*temp_env)->content)->value = ft_strdup((*data)->value);
	else
	{
		((t_env*)(*temp_env)->content)->value =
			ft_strjoin(((t_env*)(*temp_env)->content)->value, (*data)->value);
		free(*old_value);
	}
}

t_list		*ft_update_env(t_list *env, t_env *data, bool add)
{
	t_list	*temp_env;
	t_list	*to_add;
	char	*old_value;

	temp_env = ft_search_env(env, data->key);
	if (temp_env && data->value)
		ft_iftempenv(&old_value, &temp_env, &data, add);
	else if (!temp_env)
	{
		if (!(to_add = ft_lstnew(data)))
		{
			ft_free_env_lst(data);
			data = NULL;
			return (NULL);
		}
		ft_lstadd_back(&env, to_add);
	}
	if (temp_env && data)
	{
		ft_free_env_lst(data);
		data = NULL;
	}
	return (env);
}
