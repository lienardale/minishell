/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_to_lst_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 20:45:51 by cdai              #+#    #+#             */
/*   Updated: 2020/06/05 08:47:14 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

t_list			*ft_split_to_lst_env(char **env)
{
	t_list	*result;
	int		i;

	i = 0;
	result = NULL;
	while(env[i])
	{
		if (!result)
result = ft_lstnew(ft_separate_key_value(env[i]));
		else
ft_lstadd_back(&result, ft_lstnew(ft_separate_key_value(env[i])));
		i++;
	}
	return (result);
}
