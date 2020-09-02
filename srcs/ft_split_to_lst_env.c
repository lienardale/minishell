/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_to_lst_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 20:45:51 by cdai              #+#    #+#             */
/*   Updated: 2020/09/02 18:07:06 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list			*ft_split_to_lst_env(char **env)
{
	t_list	*result;
	int		i;

	i = 0;
	result = NULL;
	while (env[i])
	{
		if (!result)
			result = ft_lstnew(ft_separate_key_value(env[i]));
		else
			ft_lstadd_back(&result, ft_lstnew(ft_separate_key_value(env[i])));
		i++;
	}
	return (result);
}
