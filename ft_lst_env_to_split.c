/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_env_to_split.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 15:40:26 by cdai              #+#    #+#             */
/*   Updated: 2020/06/09 11:28:09 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

char	**ft_lst_env_to_split(t_list *lst_env)
{
	t_list	*lst;
	t_env	*content;
	char	**result;
	int		len;
	int		i;

	result = ft_calloc(ft_lstsize(lst_env) + 1, sizeof(*result));
	i = 0;
	lst = lst_env;
	while (lst)
	{
		content = (t_env*)lst->content;
		len = ft_strlen(content->key) + ft_strlen(content->value) + 2;
		result[i] = ft_calloc(len, sizeof(**result));
		ft_strlcat(result[i], content->key, len);
		ft_strlcat(result[i], "=", len);
		ft_strlcat(result[i], content->value, len);
		i++;
		lst = lst->next;
	}
	return (result);
}
