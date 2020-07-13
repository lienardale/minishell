/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 17:31:08 by cdai              #+#    #+#             */
/*   Updated: 2020/07/13 15:19:43 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int	ft_env(char **args, t_list **env)
{
	t_list	*temp;
	t_env	*content;

	temp = *env;
	if (args[1])
	{
		ft_printf("env: '%s': No such file or directory", args[1]);
		ft_free_split(args);
// return (1);
		return (1);
	}
	while (temp)
	{
		content = (t_env*)temp->content;
		if (content->value)
		{
			ft_putstr_fd(content->key, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(content->value, 1);
		}
		temp = temp->next;
	}
	ft_free_split(args);
// return (0);
	return (1);
}
