/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdai <cdai@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 07:54:41 by cdai              #+#    #+#             */
/*   Updated: 2020/06/09 13:10:38 by cdai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int	ft_export(char **args, t_list *env)
{
	int		i;
	char	**splited;

	if (!args[1])
	{
		i = -1;
		splited = ft_lst_env_to_split(env);
		ft_strs_sort(splited, ft_lstsize(env));
		while (splited[++i])
			ft_printf("%s\n", splited[i]);
		ft_free_split(splited);
	}
	else
	{
		i = 0;
		while (args[++i])
			ft_lstadd_back(&env, ft_lstnew(ft_separate_key_value(args[i])));
	}
	ft_free_split(args);
	return (1);
}
