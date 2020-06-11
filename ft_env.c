/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:31:08 by cdai              #+#    #+#             */
/*   Updated: 2020/06/11 16:54:29 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int	ft_env(char **args, t_list **env)
{
	t_list	*temp;
	t_env	*content;

	temp = *env;
	while (temp)
	{
		content = (t_env*)temp->content;
		if (content->value)
		{
			ft_putstr_fd(content->key, 0);
			ft_putstr_fd("=", 0);
			ft_putendl_fd(content->value, 0);
		}
		temp = temp->next;
	}
	ft_free_split(args);
	return (1);
}
