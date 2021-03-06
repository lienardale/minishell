/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_env_to_split.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 15:40:26 by cdai              #+#    #+#             */
/*   Updated: 2020/09/17 15:55:01 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_lst_env_to_split(t_list *lst_env)
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
		len += (content->value) ? ft_strlen(content->value) + 1 : 0;
		if (!(result[i] = ft_calloc(len, sizeof(**result)))
			&& !(ft_free_split(result)))
			return (NULL);
		ft_strlcat(result[i], content->key, len);
		if (content->value && (ft_strlcat(result[i], "=", len)))
			ft_strlcat(result[i], content->value, len);
		i++;
		lst = lst->next;
	}
	return (result);
}
