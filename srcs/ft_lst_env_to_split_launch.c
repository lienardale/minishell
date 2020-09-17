/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_env_to_split_launch.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 11:25:42 by cdai              #+#    #+#             */
/*   Updated: 2020/09/17 16:09:23 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_concat_value(char ***result, int *i, int len, t_env *content)
{
	ft_strlcat((*result)[*i], content->key, len);
	ft_strlcat((*result)[*i], "=", len);
	ft_strlcat((*result)[*i], content->value, len);
}

static int	ft_envlstlen(t_list *lst_env)
{
	int		len;
	t_list	*lst;
	t_env	*content;

	lst = lst_env;
	len = 0;
	while (lst)
	{
		content = (t_env*)lst->content;
		if (content->value)
			len++;
		lst = lst->next;
	}
	return (len);
}

char		**ft_lst_env_to_split_launch(t_list *lst_env)
{
	t_list	*lst;
	t_env	*content;
	char	**result;
	int		len;
	int		i;

	if (!(result = ft_calloc(ft_envlstlen(lst_env) + 1, sizeof(*result))))
		return (NULL);
	i = 0;
	lst = lst_env;
	while (lst)
	{
		content = (t_env*)lst->content;
		if (content->value)
		{
			len = ft_strlen(content->key) + 1;
			len += ft_strlen(content->value) + 1;
			if (!(result[i] = ft_calloc(len, sizeof(**result))))
				return (ft_free_split(result));
			ft_concat_value(&result, &i, len, content);
			i++;
		}
		lst = lst->next;
	}
	return (result);
}
