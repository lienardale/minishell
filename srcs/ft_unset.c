/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 09:51:54 by cdai              #+#    #+#             */
/*   Updated: 2020/06/11 16:56:42 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int	ft_unset(char **args, t_list **env)
{
	int		i;
	t_list	*to_erase;

	i = 1;
	(void)args;
	(void)env;
	while (args[i])
	{
// ToDo check_valid_char (isalnum)
		to_erase = ft_search_env(*env, args[i]);
// probleme de env, ce n'est pas l'adresse qui contient env donc il faut t_list **env
		ft_lstdel_between(env, to_erase->content, ft_free_env_lst);
		i++;
	}
	ft_free_split(args);
	return (1);
}
