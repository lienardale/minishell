/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 09:51:54 by cdai              #+#    #+#             */
/*   Updated: 2020/06/11 09:36:05 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int	ft_unset(char **args, t_list *env)
{
	int	i;
	t_list	*to_erase;

	i = 0;
	(void)args;
	(void)env;
	while (args[i])
	{
// ToDo check_valid_char (isalnum)
		to_erase = ft_search_env(env, args);
		ft_lstdel_between(env, to_erase->next, ft_free_env_lst);
		i++;
	}
	ft_free_split(args);
	return (1);
}
