/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 19:43:17 by cdai              #+#    #+#             */
/*   Updated: 2020/09/18 14:26:13 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*ft_check_shlvl(t_list *result)
{
	t_list	*temp_lst;
	t_env	*temp_env;

	temp_lst = ft_search_env(result, "SHLVL");
	if (!temp_lst)
	{
		temp_env = ft_new_env_var("SHLVL", "1");
		temp_lst = ft_lstnew(temp_env);
		ft_lstadd_back(&result, temp_lst);
	}
	return (result);
}

static char		*ft_increment_shlvl(char *env_shlvl)
{
	int		shlvl;
	char	*temp;
	char	*result;
	int		result_len;

	shlvl = ft_atoi(env_shlvl);
	if (!(temp = ft_itoa(++shlvl)))
		return (NULL);
	result_len = 1 + ft_strlen(temp);
	if (!(result = ft_calloc(result_len, sizeof(char))))
	{
		free(temp);
		return (NULL);
	}
	ft_strlcat(result, "", result_len);
	ft_strlcat(result, temp, result_len);
	free(temp);
	free(result);
	result = ft_itoa(shlvl);
	return (result);
}

static int		ft_isshlvl(char **old_value, char **key,
						t_list **temp, t_list **result)
{
	if (!ft_strcmp(*key, "SHLVL"))
	{
		*old_value = ((t_env*)(*temp)->content)->value;
		if (!(((t_env*)(*temp)->content)->value =
						ft_increment_shlvl(*old_value)))
		{
			ft_lstclear(result, ft_free_env_lst);
			return (0);
		}
		free(*old_value);
	}
	return (1);
}

t_list			*ft_start_minishell(char **env)
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
		if (!ft_isshlvl(&old_value, &key, &temp, &result))
			return (NULL);
		temp = temp->next;
	}
	if (!ft_check_shlvl(result))
	{
		ft_lstclear(&result, ft_free_env_lst);
		return (NULL);
	}
	return (result);
}
