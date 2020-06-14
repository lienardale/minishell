/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 19:43:17 by cdai              #+#    #+#             */
/*   Updated: 2020/06/14 14:29:12 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

static char	*ft_increment_shlvl(char *env_shlvl)
{
	int		shlvl;
//	char	*temp;
	char	*result;
//	int		result_len;

	shlvl = ft_atoi(env_shlvl);
	/*
temp = ft_itoa(++shlvl);
	result_len = 1 + ft_strlen(temp);
result = ft_calloc(result_len, sizeof(char));
	ft_strlcat(result, "", result_len);
	ft_strlcat(result, temp, result_len);
	free(temp);
*/
	result = ft_itoa(shlvl);
return (result);
}

t_list	*ft_start_minishell(char **env)
{
	char	*key;
	char	*old_value;
	t_list	*temp;
	t_list	*result;

	if (!(result = ft_split_to_lst_env(env)))
		return (NULL);
	temp = result;
	while (temp)
	{
		key = ((t_env*)temp->content)->key;
		if (!ft_strcmp(key, "SHLVL"))
		{
			old_value = ((t_env*)temp->content)->value;
			if (!(((t_env*)temp->content)->value = ft_increment_shlvl(old_value)))
			{
				ft_lstclear(&result, ft_free_env_lst);
				return (NULL);
			}
			free(old_value);
		}
printf("start_minishell/env->content->key:\t%s\n", ((t_env*)temp->content)->key);
printf("start_minishell/env->content->value:\t%s\n", ((t_env*)temp->content)->value);
		temp = temp->next;
	}
	return (result);
}
