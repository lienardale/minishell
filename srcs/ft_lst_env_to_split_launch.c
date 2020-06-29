/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_env_to_split_launch.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 11:25:42 by cdai              #+#    #+#             */
/*   Updated: 2020/07/30 14:44:32 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

char	**ft_lst_env_to_split_launch(t_list *lst_env)
{
	t_list	*lst;
	t_env	*content;
	char	**result;
	int		len;
	int		i;

	lst = lst_env;
	len = 0;
	while (lst)
	{
		content = (t_env*)lst->content;
		if (content->value)
			len++;
		lst = lst->next;
	}
	if (!(result = ft_calloc(len + 1, sizeof(*result))))
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
			{
				ft_free_split(result);
				return (NULL);
			}
			ft_strlcat(result[i], content->key, len);
			ft_strlcat(result[i], "=", len);
			ft_strlcat(result[i], content->value, len);
			i++;
		}
		lst = lst->next;
	}
	return (result);
}
