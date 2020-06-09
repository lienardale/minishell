/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 07:54:41 by cdai              #+#    #+#             */
/*   Updated: 2020/06/09 15:39:33 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

t_list	*ft_search_n_update_env(t_list *env, char *arg)
{
	t_env	*result;
	t_env	*env_content;
	t_list	*temp_env;

	temp_env = env;
	result = ft_separate_key_value(arg);
	while (temp_env)
	{
		env_content = (t_env*)temp_env->content;
		if (ft_strcmp(env_content->key, result->key) == 0)
		{
			if (result->value)
			{
				free(env_content->value);
				env_content->value = result->value;
			}
			free(result->key);
			free(result);
			return (env);
		}
		temp_env = temp_env->next;
	}
	ft_lstadd_back(&env, ft_lstnew(result));
	return (env);
}

int		ft_export(char **args, t_list *env)
{
	int		i;
	char	**splited;

	if (!args[1])
	{
		i = -1;
		splited = ft_lst_env_to_split(env);
		ft_strs_sort(splited, ft_lstsize(env));
		while (splited[++i])
			ft_printf("%s\n", splited[i]);
		ft_free_split(splited);
	}
	else
	{
		i = 0;
		while (args[++i])
			ft_search_n_update_env(env, args[i]);
	}
	ft_free_split(args);
	return (1);
}
