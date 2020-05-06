/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 08:12:21 by alienard          #+#    #+#             */
/*   Updated: 2020/05/06 13:45:27 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "v0_minishell.h"

int		ft_parse_line(char **args, char **env, int (*builtin_fct[7])(char **))
{
	char	**builtins;
	int		i;

	// builtins = ft_split("echo,exit,cd,pwd,export,unset,env", ',');
	builtins = ft_split("echo,exit", ',');
	if (args[0] == NULL)
	{
	// An empty command was entered.
		return (1);
	}
	i = -1;
	while (builtins[++i])
	{
		if (ft_strcmp(args[0], builtins[i]) == 0)
			return (builtin_fct[i](args));
	}
	return ft_launch(args, env);
}
