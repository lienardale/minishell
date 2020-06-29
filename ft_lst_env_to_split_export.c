/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_env_to_split_export.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 10:46:03 by cdai              #+#    #+#             */
/*   Updated: 2020/06/29 10:49:51 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

char	**ft_lst_env_to_split_export(t_list *lst_env)
{
	t_list	*lst;
	t_env	*content;
	char	**result;
	int		len;
	int		i;

	if (!(result = ft_calloc(ft_lstsize(lst_env) + 1, sizeof(*result))))
		return (NULL);
	i = 0;
	lst = lst_env;
	while (lst)
	{
		content = (t_env*)lst->content;
		len = ft_strlen(content->key) + 1;
		len += (content->value) ? ft_strlen(content->value) + 3 : 0;
		if (!(result[i] = ft_calloc(len, sizeof(**result))))
		{
			ft_free_split(result);
			return (NULL);
		}
		ft_strlcat(result[i], content->key, len);
		if (content->value)
		{
			ft_strlcat(result[i], "=", len);
			ft_strlcat(result[i], "\"", len);
			ft_strlcat(result[i], content->value, len);
			ft_strlcat(result[i], "\"", len);
		}
		i++;
		lst = lst->next;
	}
	return (result);
}
